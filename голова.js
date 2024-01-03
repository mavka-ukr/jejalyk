var М = Symbol("Мавка");

class Падіння extends Error {
  constructor(value) {
    super(typeof value === "string" ? value : мТекст(value));
    this.значення = value;
  }
}

var м_обʼєкт = Object.create(null);
var м_список = Array;
var м_число = Number;
var м_текст = String;
var м_логічне = Boolean;
var м_пусто = null;
var м_байти = ArrayBuffer;
var м_Модуль = Object.create(null);
var м_Дія = Function;

var м_так = true;
var м_ні = false;

function мДп(constructor, fn) {
  Object.defineProperty(constructor.prototype, fn.name, {
    get: fn,
  });
}

мДп(Array, function довжина() {
  return this.length;
});
Array.сортувати = мДія(function сортувати(список) {
  return список.sort((a, b) => a - b);
});
мДп(Array, function сортувати() {
  return (fn) => this.sort(fn);
});
мДп(Array, function додати() {
  return (value) => this.push(value);
});
мДп(Array, function забрати() {
  return () => this.pop();
});
мДп(Array, function фільтр() {
  return (fn) => this.filter(fn);
});
мДп(Array, function знайти() {
  return (fn) => this.find(fn);
});
мДп(Array, function знайти_позицію() {
  return (fn) => this.findIndex(fn);
});
мДп(Array, function позиція() {
  return (value) => this.indexOf(value);
});
мДп(Array, function перетворити() {
  return (fn) => this.map(fn);
});
мДп(Array, function зʼєднати() {
  return (d) => this.map((v) => мТекст(v)).join(d);
});
мДп(Array, function обернути() {
  return () => this.reverse();
});
мДп(Array, function зріз() {
  return (from, to) => this.slice(from, to == null ? undefined : to);
});
мДп(Array, function чародія_містить() {
  return (value) => this.findIndex((item) => item === value) !== -1;
});
мДп(Array, function чародія_отримати() {
  return (index) => this[index];
});
мДп(Array, function чародія_покласти() {
  return (index, value) => {
    this[index] = value;
    return this;
  };
});
мДп(Array, function чародія_перебір() {
  return () => {
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
  };
});
мДп(Array, function чародія_логічне() {
  return () => true;
});
мДп(Array, function чародія_текст() {
  return () => "<список>";
});

мДп(Map, function розмір() {
  return this.size;
});
мДп(Map, function ключі() {
  return () => [...this.keys()];
});
мДп(Map, function значення() {
  return () => [...this.values()];
});
мДп(Map, function видалити() {
  return (k) => {
    return this.delete(k);
  };
});
мДп(Map, function очистити() {
  return () => {
    this.clear();
    return this;
  };
});
мДп(Map, function чародія_містить() {
  return (k) => this.has(k);
});
мДп(Map, function чародія_отримати() {
  return (k) => this.get(k);
});
мДп(Map, function чародія_покласти() {
  return (k, v) => {
    this.set(k, v);
    return this;
  };
});
мДп(Map, function чародія_перебір() {
  return () => {
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
  };
});
мДп(Map, function чародія_перебір_з_ключем() {
  return () => {
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
  };
});
мДп(Map, function чародія_логічне() {
  return () => true;
});
мДп(Map, function чародія_текст() {
  return () => "<словник>";
});

Object.defineProperty(String.prototype, "довжина", {
  get: function() {
    return this.length;
  },
});
Object.defineProperty(String.prototype, "чародія_додати", {
  get: function() {
    return (value) => this + value;
  },
});

Object.defineProperty(Number.prototype, "чародія_додати", {
  get: function() {
    return (value) => this + value;
  },
});
Object.defineProperty(Number.prototype, "чародія_помножити", {
  get: function() {
    return (value) => this * value;
  },
});

Object.defineProperty(Function.prototype, "чародія_викликати", {
  get: function() {
    return (...args) => {
      return this(...args);
    };
  },
});

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
  structure.чародія_викликати = мДія(function чародія_викликати() {
    var instance = Object.create(null);
    instance[М] = Object.create(null);
    instance[М].структура = structure;
    fn(instance, ...arguments);
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
      if (v[М].структура === null) {
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
  if (typeof v === "string") {
    return v;
  }
  if (typeof v === "number") {
    return v;
  }
  if (typeof v === "boolean") {
    return v ? "так" : "ні";
  }
  return "<обʼєкт>";
}

function мНазваТипу(value) {
  if (value == null) {
    return "пусто";
  }
  if (typeof value === "boolean") {
    return "логічне";
  }
  if (typeof value === "number") {
    return "число";
  }
  if (typeof value === "string") {
    return "текст";
  }
  if (value instanceof Array) {
    return "список";
  }
  if (value instanceof Map) {
    return "словник";
  }
  if (value instanceof Uint8Array) {
    return "байти";
  }
  if (value[MAVKA]) {
    if (value[MAVKA].tdiia) {
      return `<дія ${value[MAVKA].name}>`;
    }
    if (value[MAVKA].tstructure) {
      return `<структура ${value[MAVKA].name}>`;
    }
    if (value[MAVKA].structure) {
      return value[MAVKA].structure[MAVKA].name;
    }
  }
  return "портал";
}

function мДодати(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_додати" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a + b;
  }
  if (typeof a === "string" && typeof b === "string") {
    return a + b;
  }
  var magic = a["чародія_додати"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_додати" для типу "${мНазваТипу(a)}".`);
}

function мВідняти(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_відняти" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a - b;
  }
  var magic = a["чародія_відняти"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_відняти" для типу "${мНазваТипу(a)}".`);
}

function мПомножити(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_помножити" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a * b;
  }
  var magic = a["чародія_помножити"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_помножити" для типу "${мНазваТипу(a)}".`);
}

function мПоділити(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_поділити" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a / b;
  }
  var magic = a["чародія_поділити"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_поділити" для типу "${мНазваТипу(a)}".`);
}

function мОстача(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_остача" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a % b;
  }
  var magic = a["чародія_остача"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_остача" для типу "${мНазваТипу(a)}".`);
}

function мСтепінь(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_степінь" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return Math.pow(a, b);
  }
  var magic = a["чародія_степінь"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_степінь" для типу "${мНазваТипу(a)}".`);
}

function мВабо(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_вабо" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a ^ b;
  }
  var magic = a["чародія_вабо"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_вабо" для типу "${мНазваТипу(a)}".`);
}

function мДі(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_ді" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a & b;
  }
  var magic = a["чародія_ді"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_ді" для типу "${мНазваТипу(a)}".`);
}

function мДабо(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_дабо" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a | b;
  }
  var magic = a["чародія_дабо"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_дабо" для типу "${мНазваТипу(a)}".`);
}

function мВліво(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_вліво" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a << b;
  }
  var magic = a["чародія_вліво"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_вліво" для типу "${мНазваТипу(a)}".`);
}

function мВправо(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_вправо" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >> b;
  }
  var magic = a["чародія_вправо"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_вправо" для типу "${мНазваТипу(a)}".`);
}

function мДні(a) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_дні" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number") {
    return ~a;
  }
  var magic = a["чародія_дні"];
  if (magic) {
    return magic();
  }
  throw new Падіння(`Неможливо виконати "чародія_дні" для типу "${мНазваТипу(a)}".`);
}

function мБільше(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_більше" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a > b;
  }
  var magic = a["чародія_більше"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_більше" для типу "${мНазваТипу(a)}".`);
}

function мМенше(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_менше" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a < b;
  }
  var magic = a["чародія_менше"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_менше" для типу "${мНазваТипу(a)}".`);
}

function мНеМенше(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_не_менше" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >= b;
  }
  var magic = a["чародія_не_менше"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_не_менше" для типу "${мНазваТипу(a)}".`);
}

function мНеБільше(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_не_більше" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a <= b;
  }
  var magic = a["чародія_не_більше"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_не_більше" для типу "${мНазваТипу(a)}".`);
}

function мМістить(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_містить" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "string" && typeof b === "string") {
    return a.includes(b);
  }
  if (a instanceof Array) {
    return a.includes(b);
  }
  if (a instanceof Map) {
    return a.has(b);
  }
  var magic = a["чародія_містить"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_містить" для типу "${мНазваТипу(a)}".`);
}

function мВідʼємне(a) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_відʼємне" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number") {
    return -a;
  }
  var magic = a["чародія_відʼємне"];
  if (magic) {
    return magic();
  }
  throw new Падіння(`Неможливо виконати "чародія_відʼємне" для типу "${мНазваТипу(a)}".`);
}

function мДодатнє(a) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_додатнє" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number") {
    return +a;
  }
  var magic = a["чародія_додатнє"];
  if (magic) {
    return magic();
  }
  throw new Падіння(`Неможливо виконати "чародія_додатнє" для типу "${мНазваТипу(a)}".`);
}

function мОтримати(a, b) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_отримати" для типу "${мНазваТипу(a)}".`);
  }
  if (typeof a === "string") {
    return a[b];
  }
  if (a instanceof Array) {
    return a[b];
  }
  if (a instanceof Map) {
    return a.get(b);
  }
  var magic = a["чародія_отримати"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати "чародія_отримати" для типу "${мНазваТипу(a)}".`);
}

function мПокласти(a, b, c) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати "чародія_покласти" для типу "${мНазваТипу(a)}".`);
  }
  if (a instanceof Array) {
    return a[b] = c;
  }
  if (a instanceof Map) {
    return a.set(b, c);
  }
  var magic = a["чародія_покласти"];
  if (magic) {
    return magic(b, c);
  }
  throw new Падіння(`Неможливо виконати "чародія_покласти" для типу "${мНазваТипу(a)}".`);
}

function мВикликати(a, args) {
  if (a == null) {
    throw new Падіння(`Неможливо викликати "${мНазваТипу(a)}".`);
  }
  if (a[М] && a[М].структура === Function) {
    return a(...args);
  }
  var magic = a["чародія_викликати"];
  if (magic) {
    return magic(...args);
  }
  throw new Падіння(`Неможливо викликати "${мНазваТипу(a)}".`);
}

function мЄ(a, b) {
  if (a == null && b == null) {
    return true;
  }
  if (a == null || b == null) {
    return false;
  }
  if (b === Number && typeof a === "number") {
    return true;
  }
  if (b === String && typeof a === "string") {
    return true;
  }
  if (b === Boolean && typeof a === "boolean") {
    return true;
  }
  if (b === Map && a instanceof Map) {
    return true;
  }
  if (b === Array && Array.isArray(a)) {
    return true;
  }
  if (b === Function && typeof a === "function") {
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