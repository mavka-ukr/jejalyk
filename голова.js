var М = Symbol("Мавка");

class Падіння extends Error {
  constructor(message) {
    super(message);
  }
}

var обʼєкт = Object.create(null);
var список = Array;
var число = Number;
var текст = String;
var логічне = Boolean;
var пусто = null;
var байти = ArrayBuffer;
var Модуль = Object.create(null);
var Дія = Function;

Object.defineProperty(Array.prototype, "довжина", {
  get: function() {
    return this.length;
  },
});
Object.defineProperty(Array.prototype, "додати", {
  get: function() {
    return (value) => {
      this.push(value);
      return this;
    };
  },
});
Object.defineProperty(Array.prototype, "чародія_містить", {
  get: function() {
    return (value) => this.findIndex((item) => item === value) !== -1;
  },
});
Object.defineProperty(Array.prototype, "чародія_перебір", {
  get: function() {
    return () => {
      let i = 0;
      const iterator = Object.create(null);
      iterator.завершено = this.length === 0;
      iterator.значення = this[i];
      iterator.далі = мДія("далі", () => {
        if (iterator.завершено) {
          return;
        }
        iterator.значення = this[++i];
        iterator.завершено = i >= this.length;
      });
      return iterator;
    };
  },
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

Object.defineProperty(Map.prototype, "чародія_покласти", {
  get: function() {
    return (k, v) => {
      this.set(k, v);
      return this;
    };
  },
});
Object.defineProperty(Map.prototype, "чародія_отримати", {
  get: function() {
    return (k) => {
      return this.get(k);
    };
  },
});

function мДія(name, fn) {
  fn[М] = Object.create(null);
  fn[М].структура = Дія;
  fn[М].назва = name;
  return fn;
}

function мСтруктура(name, parent, fillFn) {
  var structure = Object.create(null);
  structure[М] = Object.create(null);
  structure[М].структура = null;
  structure[М].назва = name;
  structure[М].предок = parent;
  structure[М].заповнити = fillFn;
  structure[М].методи = Object.create(null);
  structure.створити = мДія("створити", function() {
    var instance = Object.create(null);
    instance[М] = Object.create(null);
    instance[М].структура = structure;
    fillFn(instance, ...arguments);
    return instance;
  });
  structure.чародія_викликати = structure.створити;
  return structure;
}

function мВідДо(from, middleSymbol, middle, toSymbol, to) {
  const iterator = Object.create(null);
  iterator.завершено = false;
  iterator.значення = from;
  if (toSymbol === "<=") {
    iterator.завершено = iterator.значення >= to;
  } else {
    throw new Error("Unknown symbol");
  }
  iterator.далі = мДія("далі", function() {
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

async function мМодуль(name, fn) {
  const module = Object.create(null);
  module[М] = Object.create(null);
  module[М].структура = Модуль;
  module[М].назва = name;
  await fn(module);
  return module;
}

function мГарно(value) {
  const convert = (v, depth = 0) => {
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
      const entries = [...v.entries()].map(([k, v]) => `${convert(k, depth + 1)}=${convert(v, depth + 1)}`);
      return `(${entries.join(", ")})`;
    }
    if (v instanceof Uint8Array) {
      return `<байти ${v.length}>`;
    }
    if (v[М]) {
      if (v[М].структура === Дія) {
        return `<дія ${v[М].назва}>`;
      }
      if (v[М].структура === Модуль) {
        const keys = Object.keys(v).map((k) => `${k}`).join(", ");
        return `<модуль ${v[М].назва}[${keys}]>`;
      }
      if (v[М].структура === null) {
        return `<структура ${v[М].назва}>`;
      }
      if (v[М].структура) {
        const entries = Object.entries(v).map(([k, v]) => `${convert(k, depth + 1)}=${convert(v, depth + 1)}`);
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
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати додавання з "${мНазваТипу(a)}".`);
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
  throw new Падіння(`Неможливо виконати додавання з "${мНазваТипу(a)}".`);
}

function мВідняти(a, b) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати віднімання з "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a - b;
  }
  var magic = a["чародія_відняти"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати віднімання з "${мНазваТипу(a)}".`);
}

function мПомножити(a, b) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати множення з "${мНазваТипу(a)}".`);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a * b;
  }
  var magic = a["чародія_помножити"];
  if (magic) {
    return magic(b);
  }
  throw new Падіння(`Неможливо виконати множення з "${мНазваТипу(a)}".`);
}

function мОтримати(a, b) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо отримати елемент з "${мНазваТипу(a)}".`);
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
  throw new Падіння(`Неможливо отримати елемент з "${мНазваТипу(a)}".`);
}

function мПокласти(a, b, c) {
  if (a == null || b == null || c == null) {
    throw new Падіння(`Неможливо покласти елемент в "${мНазваТипу(a)}".`);
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
  throw new Падіння(`Неможливо покласти елемент в "${мНазваТипу(a)}".`);
}

function мВикликати(a, args) {
  if (a == null) {
    throw new Падіння(`Неможливо викликати "${мНазваТипу(a)}".`);
  }
  if (a[М] && a[М].структура === Дія) {
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