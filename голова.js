var М = Symbol("Мавка");

class Падіння extends Error {
  constructor(value) {
    super(мТекст(value));
    this.значення = value;
  }
}

function мДп(constructor, fn) {
  Object.defineProperty(constructor.prototype, fn.name, {
    get() {
      return (...args) => fn.apply(this, args);
    },
  });
}

function мДія(fn) {
  fn[М] = Object.create(null);
  fn[М].структура = Function;
  fn[М].назва = fn.name;
  return fn;
}

function мСтруктура(parent, fn) {
  var structure = Object.create(null);
  structure[М] = Object.create(null);
  structure[М].структура = null;
  structure[М].назва = fn.name;
  structure[М].предок = parent;
  structure[М].заповнити = fn;
  structure[М].методи = Object.create(null);
  structure.чародія_викликати = мДія(function чародія_викликати(...args) {
    var instance = Object.create(null);
    instance[М] = Object.create(null);
    instance[М].структура = structure;
    fn(instance, ...args);
    return instance;
  });
  return structure;
}

function мВідДо(from, middleSymbol, middle, toSymbol, to) {
  var iterator = Object.create(null);
  iterator.завершено = false;
  iterator.значення = from;
  if (toSymbol === "<=") {
    iterator.завершено = iterator.значення >= to;
  } else {
    throw new Error("Unknown symbol");
  }
  iterator.далі = мДія(function далі() {
    if (iterator.завершено) {
      return;
    }
    if (middleSymbol === "+") {
      iterator.значення = iterator.значення + middle;
    } else {
      throw new Error("Unknown symbol");
    }
    if (toSymbol === "<=") {
      iterator.завершено = iterator.значення > to;
    } else {
      throw new Error("Unknown symbol");
    }
  });
  return iterator;
}

async function мМодуль(fn) {
  var module = Object.create(null);
  module[М] = Object.create(null);
  module[М].структура = м_Модуль;
  module[М].назва = fn.name;
  await fn(module);
  return module;
}

function мГарно(value) {
  var convert = (v, depth = 0) => {
    var keys;
    var entries;
    if (v == null) {
      return "пусто";
    }
    if (typeof v === "boolean") {
      return v ? "так" : "ні";
    }
    if (typeof v === "number") {
      return String(v);
    }
    if (typeof v === "string") {
      if (depth === 0) {
        return v;
      }
      return `"${v}"`;
    }
    if (v instanceof Array) {
      return `[${v.map((v) => convert(v, depth + 1)).join(", ")}]`;
    }
    if (v instanceof Map) {
      entries = [...v.entries()].map(([k, v]) => `${convert(k, depth + 1)}=${convert(v, depth + 1)}`);
      return `(${entries.join(", ")})`;
    }
    if (v instanceof Uint8Array) {
      return `<байти ${v.length}>`;
    }
    if (v[М]) {
      if (v[М].структура === Function) {
        return `<дія ${v[М].назва}>`;
      }
      if (v[М].структура === м_Модуль) {
        keys = Object.keys(v).map((k) => `${k}`).join(", ");
        return `<модуль ${v[М].назва}[${keys}]>`;
      }
      if (v[М].структура === м_Структура) {
        return `<структура ${v[М].назва}>`;
      }
      if (v[М].структура) {
        entries = Object.entries(v).map(([k, v]) => `${k}=${convert(v, depth + 1)}`);
        return `${v[М].структура[М].назва}(${entries})`;
      }
    }
    return "<портал>";
  };
  return convert(value, 0);
}

function мТекст(v) {
  if (v == null) {
    return "пусто";
  }
  if (typeof v === "string") {
    return v;
  }
  if (v.чародія_текст) {
    return v.чародія_текст();
  }
  if (v[М]) {
    return "<обʼєкт>";
  }
  return "<портал>";
}

function мЄ(a, b) {
  if (b === м_обʼєкт) {
    return true;
  }
  if (a == null && b == null) {
    return true;
  }
  if (a == null || b == null) {
    return false;
  }
  if (b === м_число && typeof a === "number") {
    return true;
  }
  if (b === м_текст && typeof a === "string") {
    return true;
  }
  if (b === м_логічне && typeof a === "boolean") {
    return true;
  }
  if (b === м_словник && a instanceof Map) {
    return true;
  }
  if (b === м_список && Array.isArray(a)) {
    return true;
  }
  if (b === м_Дія && typeof a === "function") {
    return true;
  }
  var structure = a[М]?.структура;
  while (structure) {
    if (structure === b) {
      return true;
    }
    structure = structure[М]?.предок;
  }
  return false;
}

var м_обʼєкт = Object.create(null);
м_обʼєкт[М] = Object.create(null);
м_обʼєкт[М].структура = null;
м_обʼєкт[М].назва = "Обʼєкт";

var м_Структура = Object.create(null);
м_Структура[М] = Object.create(null);
м_Структура[М].структура = м_обʼєкт;
м_Структура[М].назва = "Структура";

var м_Дія = Function;
м_Дія[М] = Object.create(null);
м_Дія[М].структура = м_Структура;
м_Дія[М].назва = "Дія";
м_Дія.prototype.чародія_викликати = function чародія_викликати(...args) {
  return this(...args);
};

var м_логічне = Boolean;
м_логічне[М] = Object.create(null);
м_логічне[М].структура = м_Структура;
м_логічне[М].назва = "логічне";
мДп(м_логічне, function чародія_число() {
  return Number(this);
});
мДп(м_логічне, function чародія_текст() {
  return this ? "так" : "ні";
});

var м_число = Number;
м_число[М] = Object.create(null);
м_число[М].структура = м_Структура;
м_число[М].назва = "число";
м_число.чародія_викликати = мДія(function чародія_викликати(м_значення) {
  return м_значення.чародія_число();
});
мДп(м_число, function чародія_додати(v) {
  return this + v;
});
мДп(м_число, function чародія_відняти(v) {
  return this - v;
});
мДп(м_число, function чародія_помножити(v) {
  return this * v;
});
мДп(м_число, function чародія_поділити(v) {
  return this / v;
});
мДп(м_число, function чародія_остача(v) {
  return this % v;
});
мДп(м_число, function чародія_частка(v) {
  return Math.floor(this / v);
});
мДп(м_число, function чародія_степінь(v) {
  return this ** v;
});
мДп(м_число, function чародія_вліво(v) {
  return this << v;
});
мДп(м_число, function чародія_вправо(v) {
  return this >> v;
});
мДп(м_число, function чародія_вабо(v) {
  return this ^ v;
});
мДп(м_число, function чародія_дабо(v) {
  return this | v;
});
мДп(м_число, function чародія_ді(v) {
  return this & v;
});
мДп(м_число, function чародія_більше(v) {
  return this > v;
});
мДп(м_число, function чародія_менше(v) {
  return this < v;
});
мДп(м_число, function чародія_не_більше(v) {
  return this <= v;
});
мДп(м_число, function чародія_не_менше(v) {
  return this >= v;
});
мДп(м_число, function чародія_дні() {
  return ~this;
});
мДп(м_число, function чародія_додатнє() {
  return +this;
});
мДп(м_число, function чародія_відʼємне() {
  return -this;
});
мДп(м_число, function чародія_текст() {
  return String(this);
});

var м_текст = String;
м_текст[М] = Object.create(null);
м_текст[М].структура = м_Структура;
м_текст[М].назва = "текст";
м_текст.чародія_викликати = мДія(function чародія_викликати(м_значення) {
  return мТекст(м_значення);
});
Object.defineProperty(м_текст.prototype, "довжина", {
  get() {
    return this.length;
  },
});
мДп(м_текст, function розбити(d) {
  return this.split(d);
});
мДп(м_текст, function замінити(o, n) {
  return this.replaceAll(o, n);
});
мДп(м_текст, function починається(v) {
  return this.startsWith(v);
});
мДп(м_текст, function закінчується(v) {
  return this.endsWith(v);
});
мДп(м_текст, function обтяти() {
  return this.trim();
});
мДп(м_текст, function чародія_додати(v) {
  return this + v;
});
мДп(м_текст, function чародія_містить(v) {
  return this.includes(v);
});
мДп(м_текст, function чародія_отримати(i) {
  return this[i];
});
мДп(м_текст, function чародія_перебір() {
  var i = 0;
  var iterator = Object.create(null);
  iterator.завершено = this.length === 0;
  iterator.значення = this[i];
  var that = this;
  iterator.далі = мДія(function далі() {
    iterator.значення = that[++i];
    iterator.завершено = i >= that.length;
  });
  return iterator;
});
мДп(м_текст, function чародія_число() {
  return Number(this);
});
мДп(м_текст, function чародія_байти() {
  return new TextEncoder("utf-8").encode(this);
});

var м_список = Array;
м_список[М] = Object.create(null);
м_список[М].структура = м_Структура;
м_список[М].назва = "список";
Object.defineProperty(Array.prototype, "довжина", {
  get() {
    return this.length;
  },
});
Array.сортувати = мДія(function сортувати(список) {
  return список.sort((a, b) => a - b);
});
мДп(Array, function сортувати(fn) {
  return this.sort(fn);
});
мДп(Array, function додати(value) {
  return this.push(value);
});
мДп(Array, function забрати() {
  return this.pop();
});
мДп(Array, function фільтр(fn) {
  return this.filter(fn);
});
мДп(Array, function знайти(fn) {
  return this.find(fn);
});
мДп(Array, function знайти_позицію(fn) {
  return this.findIndex(fn);
});
мДп(Array, function позиція(value) {
  return this.indexOf(value);
});
мДп(Array, function перетворити(fn) {
  return this.map(fn);
});
мДп(Array, function зʼєднати(d) {
  return this.map((v) => мТекст(v)).join(d);
});
мДп(Array, function обернути() {
  return this.reverse();
});
мДп(Array, function зріз(from, to) {
  return this.slice(from, to == null ? undefined : to);
});
мДп(Array, function чародія_містить(value) {
  return this.findIndex((item) => item === value) !== -1;
});
мДп(Array, function чародія_отримати(index) {
  return this[index];
});
мДп(Array, function чародія_покласти(index, value) {
  this[index] = value;
  return this;
});
мДп(Array, function чародія_перебір() {
  var i = 0;
  var iterator = Object.create(null);
  iterator.завершено = this.length === 0;
  iterator.значення = this[i];
  var that = this;
  iterator.далі = мДія(function далі() {
    iterator.значення = that[++i];
    iterator.завершено = i >= that.length;
  });
  return iterator;
});
мДп(Array, function чародія_текст() {
  return "<список>";
});

var м_словник = Map;
м_словник[М] = Object.create(null);
м_словник[М].структура = м_Структура;
м_словник[М].назва = "словник";
Object.defineProperty(м_словник.prototype, "розмір", {
  get() {
    return this.size;
  },
});
мДп(Map, function ключі() {
  return [...this.keys()];
});
мДп(Map, function значення() {
  return [...this.values()];
});
мДп(Map, function видалити(k) {
  return this.delete(k);
});
мДп(Map, function очистити() {
  this.clear();
  return this;
});
мДп(Map, function чародія_містить(k) {
  return this.has(k);
});
мДп(Map, function чародія_отримати(k) {
  return this.get(k);
});
мДп(Map, function чародія_покласти(k, v) {
  this.set(k, v);
  return this;
});
мДп(Map, function чародія_перебір() {
  const keys = [...this.keys()];
  var i = 0;
  var iterator = Object.create(null);
  iterator.завершено = keys.length === 0;
  iterator.значення = keys[i];
  iterator.далі = мДія(function далі() {
    iterator.значення = keys[++i];
    iterator.завершено = i >= keys.length;
  });
  return iterator;
});
мДп(Map, function чародія_перебір_з_ключем() {
  const entries = [...this.entries()];
  var i = 0;
  var iterator = Object.create(null);
  iterator.завершено = entries.length === 0;
  iterator.ключ = entries[i][0];
  iterator.значення = entries[i][1];
  iterator.далі = мДія(function далі() {
    i++;
    iterator.ключ = entries[i][0];
    iterator.значення = entries[i][1];
    iterator.завершено = i >= entries.length;
  });
  return iterator;
});
мДп(Map, function чародія_текст() {
  return "<словник>";
});

var м_очікування = Promise;
м_очікування[М] = Object.create(null);
м_очікування[М].структура = м_Структура;
м_очікування[М].назва = "очікування";

var м_Модуль = Object.create(null);
м_Модуль[М] = Object.create(null);
м_Модуль[М].структура = м_Структура;
м_Модуль[М].назва = "Модуль";

var м_перебір = мСтруктура(м_обʼєкт, function перебір(мs, м_завершено, м_значення) {
  мs.завершено = м_завершено;
  мs.значення = м_значення;
  мs.далі = мДія(function далі() {
    м_перебір[М].методи.далі(мs);
  });
  return мs;
});
м_перебір[М].методи.далі = мДія(function далі(я) {
});
м_перебір.створити = мДія(function створити(м_завершено, м_значення, м_далі) {
  var м_новий_перебір = м_перебір.чародія_викликати(м_завершено, м_значення);
  м_новий_перебір.далі = мДія(function далі() {
    м_далі(м_новий_перебір);
  });
  return м_новий_перебір;
});

var м_байти = Uint8Array;
м_байти[М] = Object.create(null);
м_байти[М].структура = м_Структура;
м_байти[М].назва = "байти";
м_байти.чародія_викликати = мДія(function чародія_викликати(м_значення) {
  return м_значення.чародія_байти();
});
мДп(м_байти, function чародія_текст() {
  return new TextDecoder("utf-8").decode(this);
});

var м_пусто = null;
var м_так = true;
var м_ні = false;
