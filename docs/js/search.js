---
---
/**
 * URLのパラメタから検索文字列を取り出し、オブジェクトに格納して返す。
 * オブジェクトは'tags'、'keywords'キィを持つ。値は共に配列。
 * パラメタ名'q'を検索パラメタとする。
 * 検索パラメタは空白文字で区切られ、'[]'で囲まれたものはタグ名、
 * それ以外はキィワードと見なして、配列に格納する。
 */


function getQuery()
{
  // 返却するオブジェクトの初期化。
  var query = { 'tags': [], 'keywords': [] };

  // LocationオブジェクトのsearchプロパティはURLのパラメタ部の文字列。
  // searchプロパティは'?'を含むのでString.substring(1)で'?'を取り除き、
  // '&'でパラメタ名毎に分割して配列に入れる。
  var parameters = window.location.search.substring(1).split('&');

  $.each(parameters, function(index, parameterString) {
    var parameter = parameterString.split('=');
    var parameterName = parameter[0];
    var parameterValue = parameter[1];
    // パラメタ名'q'以外は無視。
    if(parameterName != 'q') return true;

    // パラメタ値をデコードし、全角空白は'+'に置換、
    // 連続する'+'はひとつに纏める。
    var decodedParameterValue = decodeURIComponent(parameterValue).replace(/　/g, '+').replace(/\++/g, '+');
    var words = decodedParameterValue.split('+');
    words.forEach(function(word) {
      var tag = word.match(/^\[(.*)\]$/);
      if(tag) query.tags.push(tag[1]);
      else query.keywords.push(word);
    });
  });

  return query;
}

// From copilot 

// 辞書(必要なものを追加)
// key/valueは大小無視で扱われます(内部で正規化)
// valueは文字列でも配列でもOK
const ALIAS_DICT = {
  "" : [""],
  // "v2l": ["rz/v2l"],
  // "v2h": ["rz/v2h"],
  // "v2n": ["rz/v2n"]
  // "ai-sdk": ["ai sdk"]
};

function normalizeToken(token) {
  // 先頭末尾の句読点/記号を除去して小文字化
  // "/"や"-"などの内部記号は残します (例: "RZ/V2L" -> "rz/v2l")
  return (token || "")
    .replace(/^[^\w]+|[^\w]+$/g, "")
    .toLowerCase();
}

function tokenizePreserveOriginal(text) {
  const original = (text || "").trim().split(/\s+/).filter((w) => w.length > 0);
  const normalized = original.map((w) => normalizeToken(w));
  return { original, normalized };
}

function buildAliasDictNormalized(aliasDict) {
  const out = {};
  for (const [k, v] of Object.entries(aliasDict || {})) {
    const key = normalizeToken(k);
    const arr = Array.isArray(v) ? v : [v];
    out[key] = arr
      .flatMap((s) => String(s).trim().split(/\s+/))
      .map((t) => normalizeToken(t))
      .filter((t) => t.length > 0);
  }
  return out;
}

function buildTargetTokenOptions(targetTokensNormalized, aliasDictNormalized) {
  // 各targetトークンごとに「許容される同義語」を配列で持つ
  // options[j] = ["v2l", "rz/v2l"] のような形
  return targetTokensNormalized.map((t) => {
    const opts = [t];
    const aliases = aliasDictNormalized[t];
    if (aliases && aliases.length > 0) {
      opts.push(...aliases);
    }
    // 重複除去
    return Array.from(new Set(opts));
  });
}

function tokenMatchAny(contentToken, targetOptions) {
  // 完全一致 or 先頭一致(例: "core" -> "core-image-weston") or 部分一致
  // + 辞書の同義語もtargetOptionsに入ってくる
  if (!contentToken || !targetOptions || targetOptions.length === 0) {
    return false;
  }

  for (const t of targetOptions) {
    if (!t) {
      continue;
    }
    if (contentToken === t) {
      return true;
    }
    if (contentToken.startsWith(t)) {
      return true;
    }
    if (contentToken.endsWith(t)) {
         return true;
    }
    if (contentToken.indexOf(t) > -1) {
      return true;
    }
    

  }
  return false;
}

function findAllMatchStartIndices(normalizedWords, targetOptionsPerToken) {
  const starts = [];
  const tLen = targetOptionsPerToken.length;
  if (tLen === 0) {
    return starts;
  }

  for (let i = 0; i <= normalizedWords.length - tLen; i++) {
    let ok = true;
    for (let j = 0; j < tLen; j++) {
      if (!tokenMatchAny(normalizedWords[i + j], targetOptionsPerToken[j])) {
        ok = false;
        break;
      }
    }
    if (ok) {
      starts.push(i);
    }
  }
  return starts;
}

function extractAllContextsWordsBold(pageContent, target, windowWords = 10, aliasDict = ALIAS_DICT) {
  if (!pageContent || !target) {
    return [];
  }

  const { original, normalized } = tokenizePreserveOriginal(pageContent);

  const targetTokensOriginal = target.trim().split(/\s+/).filter((w) => w.length > 0);
  const targetTokensNormalized = targetTokensOriginal
    .map((w) => normalizeToken(w))
    .filter((w) => w.length > 0);
  if (targetTokensNormalized.length === 0) {
    return [];
  }

  const aliasDictNormalized = buildAliasDictNormalized(aliasDict);
  const targetOptionsPerToken = buildTargetTokenOptions(targetTokensNormalized, aliasDictNormalized);

  const hitStarts = findAllMatchStartIndices(normalized, targetOptionsPerToken);
  if (hitStarts.length === 0) {
    return [];
  }

  const tLen = targetOptionsPerToken.length;

  return hitStarts.map((startIndex) => {
    const sliceStart = Math.max(0, startIndex - windowWords);
    const sliceEnd = Math.min(original.length, startIndex + tLen + windowWords);

    const parts = [];
    for (let k = sliceStart; k < sliceEnd; k++) {
      const w = original[k];
      if (k >= startIndex && k < startIndex + tLen) {
        parts.push("<strong>" + w + "</strong>");
      } else {
        parts.push(w);
      }
    }
    return parts.join(" ");
  });
}

function escapeRegExp(s) {
  return String(s).replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
}

$(function() {
  var query = getQuery();
  var queryString = '';  // input要素に表示する文字列
  query.tags.forEach(function(tagName) {
    queryString += '[' + tagName + '] ';
  });
  queryString += query.keywords.join(' ');
  $('#globalNavigation form input[type="search"]').val(queryString);

  var matchedPosts = [];
  var mathcedPageNum = 0;
  $('#search_keyword').append('"'+queryString+'"');
  $.getJSON('{{ site.baseurl }}/search.json', function(posts) {
    posts.forEach(function(pageInfo) {
        var regexpString = '';
        if(query.keywords.length == 1) regexpString = escapeRegExp(query.keywords[0]);
        else {
          query.keywords.forEach(function(keyword) {
            regexpString += '(?=.*' + escapeRegExp(keyword) + ')';
          });
        }
        var regExp = new RegExp(regexpString, 'i');
        if(pageInfo.title.match(regExp) != null || pageInfo.content.match(regExp) != null) {
          matchedPosts.push(pageInfo);
        // }
      }
    });
  
    // 検索条件に合致した記事があった場合は、
    // ページ内の'#matchedList'に流し込む。
    matchedList_str = '<ul type="none">';
    if(matchedPosts.length) {
      // var dl = $('<ul type="none">');
      matchedContents = [];
      matchedPosts.forEach(function(pageInfo) {
        if(!pageInfo.title.length) pageInfo.title = 'untitled';
        content_str = "";
        contexts = extractAllContextsWordsBold(pageInfo.content, queryString);
        const hitNum = contexts.length

        if (hitNum > 0)
        {
          content_str += '<hr style="border-top: 1px solid grey;"></hr>';
          content_str += '<li>';
          content_str += '<a href="' + pageInfo.url + '">' + pageInfo.title +'</a><br>';
          content_str += '<h6 class="mb-2">'+hitNum+' hits at {{ site.url }}{{ site.baseurl }}'+ pageInfo.url + '</h6>';
          content_str += '<h6 class="mb-2" style="color: gray;">'
            + '<ul type="circle" class="mb-1">'
            + '<li>... ';
          if (hitNum > 20){
            const show = contexts.slice(0, 20).join(" ...<br></li><li>... ");
            const hide = contexts.slice(20).join(" ...<br></li><li>... ");
            content_str += show 
              + '...<br></li>'
              + 'and more...<br>';
              + '</ul>'
          }
          else{
            content_str += contexts.join(" ...<br></li><li>... ")
            + ' ...<br></li>'
            + '</ul>';
          }
          content_str += '</h6></li><br>';
          mathcedPageNum++;
          matchedContents.push({ hit: hitNum, str: content_str});
        }
      });
      matchedContents.sort((a, b)=> b.hit - a.hit);
      matchedList_str += matchedContents.map (a => a.str).join("");
      matchedList_str += '</ul>';
      
      $('#matchedList').append(matchedList_str);
      $('#matchedPageNum').append(mathcedPageNum+' pages found.');
    }
    else $('#matchedList').append('<p>no search result.</p>');
  });
});
