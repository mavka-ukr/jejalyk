var М = Symbol("Мавка");
var обʼєкт = Object.create(null);

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

let друк;
//[JS]
друк = мДія("друк", function(values) {
  console.log(...values);
});
//[/JS]
let м1, м2, помножити_матриці;
помножити_матриці = мДія("помножити_матриці", function(мат1, мат2) {
  let д_мат1, д_мат1_в, д_мат3, д_мат3_в, мат3, мат4;
  let _мit_3;
  let _мit_1;
  д_мат1 = (мат1.довжина - 1);
  д_мат1_в = (мат1[0].довжина - 1);
  мат3 = [];
  for (_мit_1 = мВідЧерезДо(0, "+", 1, "<=", д_мат1_в); !(_мit_1.завершено); _мit_1.далі()) {
    let т, х;
    let _мit_2;
    х = _мit_1.значення;
    т = [];
    for (_мit_2 = мВідЧерезДо(0, "+", 1, "<=", д_мат1); !(_мit_2.завершено); _мit_2.далі()) {
      let х1;
      х1 = _мit_2.значення;
      т[х1] = (мат1[х1][х] * мат2[х]);
    }
    _мit_2 = undefined;
    мат3[х] = т;
  }
  _мit_1 = undefined;
  д_мат3 = (мат3.довжина - 1);
  д_мат3_в = (мат3[0].довжина - 1);
  мат4 = [];
  for (_мit_3 = мВідЧерезДо(0, "+", 1, "<=", д_мат3_в); !(_мit_3.завершено); _мit_3.далі()) {
    let х;
    let _мit_4;
    х = _мit_3.значення;
    мат4[х] = 0;
    for (_мit_4 = мВідЧерезДо(0, "+", 1, "<=", д_мат3); !(_мit_4.завершено); _мit_4.далі()) {
      let х1;
      х1 = _мit_4.значення;
      мат4[х] = (мат4[х] + мат3[х1][х]);
    }
    _мit_4 = undefined;
  }
  _мit_3 = undefined;
  return мат4;
});
м1 = [1, 1];
м2 = [[0.8784, 0.1216], [1.5670, 0.4330], [0.5722, -0.0722]];
друк([помножити_матриці(м2, м1)]);
