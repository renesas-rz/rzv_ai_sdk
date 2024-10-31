#include "kuhn_munkres.h"

namespace kuhn_munkres {
using std::max;

KuhnMunkres::KuhnMunkres() {

}

KuhnMunkres::~KuhnMunkres() {

}

vector<pair<int, int> > KuhnMunkres::compute(const Vec2f& costMatrix) {
    this->C = KuhnMunkres::padMatrix(costMatrix);
    this->n = C.size();
    this->originalLength = costMatrix.size();
    this->originalWidth = costMatrix.size() == 0 ? 0 : costMatrix[0].size();
    this->rowCovered = Vec1b(n, false);
    this->colCovered = Vec1b(n, false);
    this->Z0_r = 0;
    this->Z0_c = 0;
    this->path = Vec2i(n*n, Vec1i(2));
    this->marked = KuhnMunkres::makeMatrix(n, 0);
    vector<StepFunc> steps = {
        nullptr,
        &KuhnMunkres::step1,
        &KuhnMunkres::step2,
        &KuhnMunkres::step3,
        &KuhnMunkres::step4,
        &KuhnMunkres::step5,
        &KuhnMunkres::step6,
    };

    int step = 1;
    while (true) {
        if (step < 1 || step > 6) break; // done
        
        StepFunc func = steps[step];
        step = (this->*func)();
    }

    vector<pair<int, int> > result;
    for (int i = 0; i < this->originalLength; ++i)
        for (int j = 0; j < this->originalWidth; ++j)
            if (this->marked[i][j] == 1)
                result.push_back({i, j});

    return result;
}

Vec2f KuhnMunkres::makeCostMatrix(const Vec2f& profixMatrix, InversionFunc func) {
    if (func == nullptr) {
        float maxinum = -__FLT_MAX__;
        for (Vec1f row : profixMatrix)
            maxinum = std::max(maxinum, *std::max_element(row.begin(), row.end()));

        func = [maxinum](float x)->float { return maxinum - x; };
    }

    Vec2f costMatrix = profixMatrix;
    for (int i = 0; i < costMatrix.size(); ++i) {
        for (int j = 0; j < costMatrix[i].size(); ++j) {
            costMatrix[i][j] = func(costMatrix[i][j]);
        }
    }

    return costMatrix;
}

Vec2f KuhnMunkres::padMatrix(const Vec2f& matrix, const float padValue) {
    int maxColumns = 0;
    int totalRows = matrix.size();
    for (auto row : matrix) maxColumns = max(maxColumns, int(row.size()));
    totalRows = max(totalRows, maxColumns);

    Vec2f newMatrix;
    for (auto row : matrix) {
        auto newRow = row;
        while (newRow.size() < totalRows)
            // Row too short, pad it.
            newRow.push_back(padValue);
        newMatrix.push_back(newRow);
    }

    while (newMatrix.size() < totalRows)
        newMatrix.push_back(Vec1f(totalRows, padValue));

    return newMatrix;
}

Vec2i KuhnMunkres::makeMatrix(const int &n, const int &val) {
    return Vec2i(n, Vec1i(n, val));
}

int KuhnMunkres::step1() {
    for (int i = 0; i < this->n; ++i) {
        float minVal = *std::min_element(this->C[i].begin(), this->C[i].end());
        // Find the minimum value for this row and substract that mininum
        // from every element in the row.
        for (int j = 0; j < this->n; ++j)
            this->C[i][j] -= minVal;
    }

    return 2;
}

int KuhnMunkres::step2() {
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (this->C[i][j] == 0 && !this->colCovered[j] && !this->rowCovered[i]) {
                this->marked[i][j] = 1;
                this->colCovered[j] = true;
                this->rowCovered[i] = true;
                break;
            }
        }
    }

    clearCovers();
    return 3;
}

int KuhnMunkres::step3() {
    int count = 0;
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (this->marked[i][j] == 1 and !this->colCovered[j]) {
                this->colCovered[j] = true;
                count += 1;
            }
        }
    }

    if (count >= this->n) return 7; // done
    else return 4;
}

int KuhnMunkres::step4() {
    int row = 0, col = 0, starCol = -1;
    while (true) {
        auto [r, c] = findAZero(row, col);
        row = r, col = c;
        if (row < 0) {
            return 6;
        } else {
            this->marked[row][col] = 2;
            starCol = findStarInRow(row);
            if (starCol >= 0) {
                col = starCol;
                this->rowCovered[row] = true;
                this->colCovered[col] = false;
            } else {
                this->Z0_r = row;
                this->Z0_c = col;
                return 5;
            }
        }
    }
}

int KuhnMunkres::step5() {
    int count = 0;
    this->path[count][0] = this->Z0_r;
    this->path[count][1] = this->Z0_c;
    while (true) {
        int row = findStarInCol(this->path[count][1]);
        if (row >= 0) {
            count += 1;
            this->path[count][0] = row;
            this->path[count][1] = this->path[count - 1][1];

            int col = findPrimeInRow(this->path[count][0]);
            count += 1;
            this->path[count][0] = this->path[count - 1][0];
            this->path[count][1] = col;
        } else {
            this->convertPath(path, count);
            this->clearCovers();
            this->erasePrimes();
            return 3;
        }
    }
}

int KuhnMunkres::step6() {
    float minVal = findSmallest();
    int events = 0; // track actual changes to matrix
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (this->rowCovered[i]) {
                this->C[i][j] += minVal;
                events += 1;
            }

            if (!this->colCovered[j]) {
                this->C[i][j] -= minVal;
                events += 1;
            }

            if (this->rowCovered[i] && !this->colCovered[j]) {
                events -= 2;    // change reversed, no real difference
            }
        }
    }

    if (events == 0) throw UnsolvableMatrixException();

    return 4;
}

float KuhnMunkres::findSmallest() const {
    float minVal = __FLT_MAX__;
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (!this->rowCovered[i] && !this->colCovered[j] && minVal > this->C[i][j]) {
                minVal = this->C[i][j];
            }
        }
    }
    
    return minVal;
}

pair<int, int> KuhnMunkres::findAZero(const int i0, const int j0) const {
    int row = -1, col = -1;
    int i = i0;
    bool done = false;

    while (!done) {
        int j = j0;
        while (true) {
            if (this->C[i][j] == 0 && !this->rowCovered[i] & !this->colCovered[j]) {
                row = i;
                col = j;
                done = true;
            }
            j = (j + 1) % this->n;
            if (j == j0) break;
        }
        i = (i + 1) % this->n;
        if (i == i0) done = true;
    }

    return {row, col};
}

int KuhnMunkres::findStarInRow(const int row) const {
    for (int j = 0; j < this->n; ++j)
        if (this->marked[row][j] == 1)
            return j;

    return -1;
}

int KuhnMunkres::findStarInCol(const int col) const {
    for (int i = 0; i < this->n; ++i)
        if (this->marked[i][col] == 1)
            return i;

    return -1;
}

int KuhnMunkres::findPrimeInRow(const int row) const {
    for (int j = 0; j < this->n; ++j)
        if (this->marked[row][j] == 2)
            return j;

    return -1;
}

void KuhnMunkres::convertPath(const Vec2i& path, const int count) {
    for (int i = 0; i < count + 1; ++i) {
        if (this->marked[path[i][0]][path[i][1]] == 1)
            this->marked[path[i][0]][path[i][1]] = 0;
        else
            this->marked[path[i][0]][path[i][1]] = 1;
    }
}

void KuhnMunkres::clearCovers() {
    for (int i = 0; i < this->n; ++i) {
        this->rowCovered[i] = false;
        this->colCovered[i] = false;
    }
}

void KuhnMunkres::erasePrimes() {
    for (int i = 0; i < this->n; ++i)
        for (int j = 0; j < this->n; ++j)
            if (this->marked[i][j] == 2)
                this->marked[i][j] = 0;
}

} // namespace kuhn_munkres