var М = Symbol("Мавка");

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