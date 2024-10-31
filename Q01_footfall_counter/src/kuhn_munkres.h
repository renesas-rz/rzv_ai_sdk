/**
 * @desc:   Kuhn Munkres assignment algorithm
 *          link:
 *              https://brc2.com/the-algorithm-workshop/
 *              https://github.com/bmc/munkres
 *          
 * @author: lst
 * @date:   10/10/2022
 */
#pragma once

#include <vector>
#include <memory>
#include <functional>

namespace kuhn_munkres {

using std::vector;
using std::pair;
using Vec1f = vector<float>;
using Vec2f = vector<Vec1f>;
using Vec1i = vector<int>;
using Vec2i = vector<Vec1i>;
using Vec1b = vector<bool>;
using InversionFunc = std::function<float(float)> ;

class UnsolvableMatrixException : public std::exception {
    virtual const char*
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        return "Matrix cannot be solved!";
    }
};

class KuhnMunkres {
public:
    using Ptr = std::shared_ptr<KuhnMunkres>;

    // variables

    // methods
    KuhnMunkres();
    virtual ~KuhnMunkres();
    KuhnMunkres(const KuhnMunkres&) = delete;
    KuhnMunkres& operator=(const KuhnMunkres&) = delete;

    /**
     * @brief Compute the indexes for the lowest-cost pairings between rows and
     *        columns in the database. Returns a list of `(row, column)` tuples
     *        that can be used to traverse the matrix.
     *        **WARNING**: This code handles square and rectangular matrices. It
     *        does *not* handle irregular matrices.
     * @param costMatrix    (list of lists of numbers): The cost matrix. If this
     *                      cost matrix is not square, it will be padded with zeros, via a call
     *                      to `pad_matrix()`. (This method does *not* modify the caller's
     *                      matrix. It operates on a copy of the matrix.)
     * @return A list of `(row, column)` tuples that describe the lowest cost path
     *         through the matrix
     */
    vector<pair<int, int> > compute(const Vec2f& costMatrix);

    /**
     * @brief Create a cost matrix from a profit matrix by calling `inversion_function()`
     *        to invert each value. The inversion function must take one numeric argument
     *        (of any type) and return another numeric argument which is presumed to be
     *        the cost inverse of the original profit value. If the inversion function
     *        is not provided, a given cell's inverted value is calculated as
     *        `max(matrix) - value`.
     *        This is a static method. Call it like this:
     *          auto costMatrix = KuhnMunkres::makeCostMatrix(matrix, inversionFunc)
     *        For example:     
     *          auto costmatrix = KuhnMunkres::makeCostMatrix(matrix, [](float x)->float { return 1.0f - x; }])
     * @param profitMatrix  (list of lists of numbers): The matrix to convert from
     *                      profit to cost values.
     * @param func          (`function`): The function to use to invert each
     *                      entry in the profit matrix.
     * @return cost matrix
     */
    static Vec2f makeCostMatrix(const Vec2f& profixMatrix, InversionFunc func=nullptr);

private:
    using StepFunc = int (KuhnMunkres::*)();

    // variables
    Vec2f C;    // cost matrix
    Vec1b rowCovered, colCovered;
    int n = 0, originalLength = 0, originalWidth = 0;
    int Z0_r = 0, Z0_c = 0;
    Vec2i marked, path;

    // methods
    /**
     * @brief Pad a possibly non-square matrix to make it square.
     * @param matrix    matrix to pad
     * @param padValue  value to use to pad the matrix
     * @return a new, possibly padded, matrix
     */
    static Vec2f padMatrix(const Vec2f& matrix, const float padValue=0.0);

    /**
     * @brief Create an *n*x*n* matrix, populating it with the specific value.
     * @param n     rows and columns
     * @param val   value
     * @return created matrix
     */
    static Vec2i makeMatrix(const int &n, const int &val);

    /**
     * @brief For each row of the matrix, find the smallest element and
     *        substract it from every element in its row. Go to Step 2.
     * @return Next step.
     */
    int step1();

    /**
     * @brief Find a zero (Z) in the resulting matrix. If there is no starred
     *        zero in its row or column, star Z. Repeat for each element in the
     *        matrix. Go to Step 3.
     * @return Next step.
     */
    int step2();

    /**
     * @brief Cover each column containing a starred zero. If K columns are
     *        covered, the starred zeros describe a complete set of unique
     *        assignments. In this case, Go to DONE, otherwise, Go to Step 4.
     * @return Next step.
     */
    int step3();

    /**
     * @brief Find a noncovered zero and prime it. If there is no starred zero
     *        in the row containing this primed zero, Go to Step 5. Otherwise,
     *        cover this row and uncover the column containing the starred
     *        zero. Continue in this manner until there are no uncovered zeros
     *        left. Save the smallest uncovered value and Go to Step 6.
     * @return Next step.
     */
    int step4();

    /**
     * @brief Construct a series of alternating primed and starred zeros as
     *        follows. Let Z0 represent the uncovered primed zero found in Step 4.
     *        Let Z1 denote the starred zero in the column of Z0 (if any).
     *        Let Z2 denote the primed zero in the row of Z1 (there will always
     *        be one). Continue until the series terminates at a primed zero
     *        that has no starred zero in its column. Unstar each starred zero
     *        of the series, star each primed zero of the series, erase all
     *        primes and uncover every line in the matrix. Return to Step 3
     * @return Next step.
     */
    int step5();

    /**
     * @brief Add the value found in Step 4 to every element of each covered
     *        row, and subtract it from every element of each uncovered column.
     *        Return to Step 4 without altering any stars, primes, or covered
     *        lines.
     * @return Next step.
     */
    int step6();

    /**
     * @brief Find the first uncovered element with value 0
     * @return first uncovered element
     */
    float findSmallest() const;

    /**
     * @brief Find the first uncovered element with value 0
     * @param i0    start row
     * @param j0    start column
     * @return row and column index.
     */
    pair<int, int> findAZero(const int i0=0, const int j0=0) const;

    /**
     * @brief Find the first starred element in the specified row. Returns
     *        the column index, or -1 if no starred element was found.
     * @param row   row index
     * @return column index.
     */
    int findStarInRow(const int row) const;

    /**
     * @brief Find the first starred element in the specified row. Returns
     *        the row index, or -1 if no starred element was found.
     * @param col   column index
     * @return row index.
     */
    int findStarInCol(const int col) const;

    /**
     * @brief Find the first prime element in the specified row. Returns
     *        the column index, or -1 if no starred element was found.
     * @param row   row index
     * @return column index
     */
    int findPrimeInRow(const int row) const;

    void convertPath(const Vec2i& path, const int count);

    /**
     * @brief Clear all covered matrix cells
     */
    void clearCovers();

    /**
     * @brief Erase all prime markings
     */
    void erasePrimes();
};

} // namespace kuhn_munkres