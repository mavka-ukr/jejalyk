var М = Symbol("Мавка");

var обʼєкт = Object.create(null);

var список = Array;
Object.defineProperty(Array.prototype, "довжина", {
  get: function() {
    return this.length;
  },
});

function мДія(name, fn) {
  fn[М] = Object.create(null);
  fn[М].структура = Function;
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

function мВідЧерезДо(from, middleSymbol, middle, toSymbol, to) {
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