class Падіння {
  constructor(value, di) {
    this.value = value;
    this.di = di;
  }
}

var MAVKA = Symbol("мавка");

var mavka_utf8Decoder = new TextDecoder("utf-8");
var mavka_utf8Encoder = new TextEncoder("utf-8");

var м_пусто = null;

var м_логічне = Boolean;
м_логічне["чародія_викликати"] = мДія("чародія_викликати", [мПарм("значення")], function(args, di) {
  var value = args[0] ?? args["значення"];
  if (value["чародія_перетворити_на_логічне"]) {
    return мВикл(value["чародія_перетворити_на_логічне"], [value], di);
  }
  return Boolean(value);
});
м_логічне["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура логічне>";
});
var м_так = true;
var м_ні = false;

var м_число = Number;
м_число["чародія_викликати"] = мДія("чародія_викликати", [мПарм("значення")], function(args, di) {
  var value = args[0] ?? args["значення"];
  if (value["чародія_перетворити_на_число"]) {
    return мВикл(value["чародія_перетворити_на_число"], [value], di);
  }
  return Number(value);
});
м_число["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура число>";
});

var м_текст = String;
м_текст["чародія_викликати"] = мДія("чародія_викликати", [мПарм("значення")], function(args, di) {
  var value = args[0] ?? args["значення"];
  if (value == null) {
    return "пусто";
  }
  if (value["чародія_перетворити_на_текст"]) {
    return мВикл(value["чародія_перетворити_на_текст"], [], di);
  }
  if (typeof value === "string") {
    return value;
  }
  if (typeof value === "number") {
    return String(value);
  }
  if (typeof value === "boolean") {
    return value ? "так" : "ні";
  }
  if (value instanceof Array) {
    return "<список>";
  }
  if (value instanceof Map) {
    return "<словник>";
  }
  if (value instanceof Uint8Array) {
    return mavka_utf8Decoder.decode(value);
  }
  if (value[MAVKA]) {
    return "<обʼєкт>";
  }
  return "<js>";
});
м_текст["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура текст>";
});
Object.defineProperty(м_текст.prototype, "довжина", {
  get() {
    return this.length;
  },
});
Object.defineProperty(м_текст.prototype, "обрізати", {
  get() {
    return мДія("обрізати", [], () => {
      return this.trim();
    });
  },
});

var м_Дія = Function;
м_Дія["чародія_викликати"] = мДія("чародія_викликати", [], function() {
  return null;
});
м_Дія["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура Дія>";
});

var м_список = Array;
м_список["чародія_викликати"] = мДія("чародія_викликати", [], function() {
  return [];
});
м_список["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура список>";
});
Object.defineProperty(м_список.prototype, "довжина", {
  get() {
    return this.length;
  },
});
Object.defineProperty(м_список.prototype, "додати", {
  get() {
    return мДія("додати", [], (args) => {
      this.push(...Object.values(args));
      return this;
    });
  },
});

var м_байти = Uint8Array;
м_байти["чародія_викликати"] = мДія("чародія_викликати", [мПарм("значення")], function(args, di) {
  var value = args[0] ?? args["значення"];
  if (value instanceof Uint8Array) {
    return value;
  }
  if (typeof value === "string") {
    return mavka_utf8Encoder.encode(value);
  }
  throw new Падіння("Неможливо перетворити на байти.", di);
});
м_байти["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура байти>";
});
var м_словник = Map;
м_словник["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура словник>";
});

function мДія(name, params, fn) {
  var diiaValue = function(...args) {
    return fn(args);
  };
  diiaValue[MAVKA] = Object.create(null);
  diiaValue[MAVKA].name = name;
  diiaValue[MAVKA].params = params;
  diiaValue[MAVKA].perform = fn;
  return diiaValue;
}

function мСтрк(name, params, parent, di) {
  var structureValue = Object.create(null);
  structureValue[MAVKA] = Object.create(null);
  structureValue[MAVKA].name = name;
  structureValue[MAVKA].params = parent ? [...params, ...parent[MAVKA].params] : params;
  for (const param of structureValue[MAVKA].params) {
    const duplicateParam = structureValue[MAVKA].params.find((p) => p !== param && p.get("назва") === param.get("назва"));
    if (duplicateParam) {
      throw new Падіння(`Властивість "${param.get("назва")}" в "${name}" вже визначено в батьківській структурі.`, di);
    }
  }
  structureValue[MAVKA].parent = parent;
  structureValue[MAVKA].methods = parent ? [...parent[MAVKA].methods] : [];
  structureValue["чародія_викликати"] = мДія("чародія_викликати", [], function(args, di) {
    var instance = Object.create(null);
    instance[MAVKA] = Object.create(null);
    instance[MAVKA].structure = structureValue;
    for (var method of structureValue[MAVKA].methods) {
      ((function() {
        var methodName = method.get("назва");
        var methodParams = method.get("параметри");
        var methodFn = method.get("функція");
        instance[methodName] = мДія(methodName, methodParams, function(methodArgs, di) {
          return methodFn(instance, methodArgs, di);
        });
      })());
    }
    if (instance["чародія_створити"]) {
      for (let i = 0; i < structureValue[MAVKA].params.length; i++) {
        const param = structureValue[MAVKA].params[i];
        const paramName = param.get("назва");
        instance[paramName] = param.get("значення");
      }
      мВикл(instance["чародія_створити"], args, di);
    } else {
      for (let i = 0; i < structureValue[MAVKA].params.length; i++) {
        const param = structureValue[MAVKA].params[i];
        const paramName = param.get("назва");
        if (args[i] !== undefined) {
          instance[paramName] = args[i];
        } else if (args[paramName] !== undefined) {
          instance[paramName] = args[paramName];
        } else {
          instance[paramName] = param.get("значення");
        }
      }
    }
    return instance;
  });
  return structureValue;
}

function мСпрд(me, di) {
  if (me[MAVKA].cachedParent) {
    return me[MAVKA].cachedParent;
  }
  const parentValue = Object.create(null);
  parentValue[MAVKA] = Object.create(null);
  if (me[MAVKA].structure[MAVKA].parent) {
    for (const method of me[MAVKA].structure[MAVKA].parent[MAVKA].methods) {
      ((function() {
        var methodName = method.get("назва");
        var methodParams = method.get("параметри");
        var methodFn = method.get("функція");
        parentValue[methodName] = мДія(methodName, methodParams, function(methodArgs) {
          return methodFn(me, methodArgs);
        });
      })());
    }
  }
  me[MAVKA].cachedParent = parentValue;
  return parentValue;
}

async function мМодл(name, fn, di) {
  var moduleValue = Object.create(null);
  moduleValue[MAVKA] = Object.create(null);
  moduleValue[MAVKA].name = name;
  await fn(moduleValue);
  return moduleValue;
}

function мДати(module, name, value, di) {
  module[name] = value;
  return value;
}

function мВМтд(structure, method, di) {
  structure[MAVKA].methods.push(method);
}

function мМетд(name, params, fn) {
  return new Map([
    ["назва", name],
    ["параметри", params],
    ["функція", fn],
  ]);
}

function мПарм(name, type, defaultValue) {
  return new Map([
    ["назва", name],
    ["тип", type],
    ["значення", defaultValue],
  ]);
}

function мВпрм(name, type, defaultValue) {
  return new Map([
    ["назва", name],
    ["тип", type],
    ["значення", defaultValue],
    ["варіативний", true],
  ]);
}

function мВстн(a, name, value, di) {
  if (a == null) {
    throw new Падіння(`Неможливо змінити властивіть "${name}" для "пусто".`, di);
  }
  if (a instanceof Map) {
    a.set(name, value);
    return value;
  }
  a[name] = value;
  return value;
}

function мІтер(value, di) {
  if (value == null) {
    throw new Падіння(`Неможливо перебрати "пусто".`, di);
  }
  if (value[Symbol.iterator]) {
    return value;
  }
  throw new Падіння(`Неможливо перебрати.`, di);
}

function мІтерП(value, di) {
  if (value == null) {
    throw new Падіння(`Неможливо перебрати "пусто".`, di);
  }
  if (value instanceof Map) {
    return value.entries();
  }
  return Object.entries(value);
}

function* мЦВід(from, to, operation, fn, di) {
  if (operation === "==") {
    for (let i = from; i === to; i = fn(i)) {
      yield i;
    }
  } else if (operation === "<=") {
    for (let i = from; i <= to; i = fn(i)) {
      yield i;
    }
  } else if (operation === "<") {
    for (let i = from; i < to; i = fn(i)) {
      yield i;
    }
  } else if (operation === ">=") {
    for (let i = from; i >= to; i = fn(i)) {
      yield i;
    }
  } else if (operation === ">") {
    for (let i = from; i > to; i = fn(i)) {
      yield i;
    }
  } else {
    throw new Падіння(`Невідома операція "${operation}".`, di);
  }
}

function мЦВідФ(operation, step, di) {
  if (operation === "+") {
    return function(value) {
      return value + step;
    };
  }
  if (operation === "-") {
    return function(value) {
      return value - step;
    };
  }
  if (operation === "*") {
    return function(value) {
      return value * step;
    };
  }
  if (operation === "/") {
    return function(value) {
      return value / step;
    };
  }
  if (operation === "%") {
    return function(value) {
      return value % step;
    };
  }
  if (operation === "//") {
    return function(value) {
      return value % step;
    };
  }
  throw new Падіння(`Невідома операція "${operation}".`, di);
}

function мПклс(a, index, value, di) {
  if (a == null) {
    throw new Падіння(`Неможливо встановити спеціальну властивість для "пусто".`, di);
  }
  var aSetSpecialFn = a["чародія_змінити_спеціальну_властивість"];
  if (aSetSpecialFn) {
    return мВикл(aSetSpecialFn, [index, value], di);
  }
  a[index] = value;
  return value;
}

function мВикл(value, args, di) {
  if (value == null) {
    throw new Падіння(`Неможливо виконати "пусто".`, di);
  }
  var valueCallFn = value["чародія_викликати"];
  if (valueCallFn) {
    return мВикл(valueCallFn, args, di);
  }
  if (typeof value === "function") {
    var valueMavkaValue = value[MAVKA];
    if (valueMavkaValue) {
      var valueMavkaValuePerform = valueMavkaValue.perform;
      if (valueMavkaValuePerform) {
        return valueMavkaValuePerform(args);
      }
    }
    return value(...Object.values(args));
  }
  throw new Падіння("Неможливо виконати.", di);
}

function мДодт(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати додавання з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a + b;
  }
  if (typeof a === "string" && typeof b === "string") {
    return a + b;
  }
  var aSubtractFn = a["чародія_додати"];
  if (aSubtractFn) {
    return мВикл(aSubtractFn, [b], di);
  }
  throw new Падіння("Неможливо виконати додавання.", di);
}

function мВідн(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати віднімання з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a - b;
  }
  var aSubtractFn = a["чародія_відняти"];
  if (aSubtractFn) {
    return мВикл(aSubtractFn, [b], di);
  }
  throw new Падіння("Неможливо виконати віднімання.", di);
}

function мМнож(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати множення з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a * b;
  }
  var aMultiplyFn = a["чародія_помножити"];
  if (aMultiplyFn) {
    return мВикл(aMultiplyFn, [b], di);
  }
  throw new Падіння("Неможливо виконати множення.", di);
}

function мДілт(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a / b;
  }
  var aDivideFn = a["чародія_поділити"];
  if (aDivideFn) {
    return мВикл(aDivideFn, [b], di);
  }
  throw new Падіння("Неможливо виконати ділення.", di);
}

function мОстч(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення за модулем остача з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a % b;
  }
  var aModFn = a["чародія_поділити_за_модулем_остача"];
  if (aModFn) {
    return мВикл(aModFn, [b], di);
  }
  throw new Падіння("Неможливо виконати ділення за модулем остача.", di);
}

function мСтпн(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати піднесення до степеня з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return Math.pow(a, b);
  }
  var aDivDivFn = a["чародія_піднести_до_степеня"];
  if (aDivDivFn) {
    return мВикл(aDivDivFn, [b], di);
  }
  throw new Падіння("Неможливо виконати піднесення до степеня.", di);
}

function мОст2(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення за модулем частка з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return Math.floor(a / b);
  }
  var aDivDivFn = a["чародія_поділити_за_модулем_частка"];
  if (aDivDivFn) {
    return мВикл(aDivDivFn, [b], di);
  }
  throw new Падіння("Неможливо виконати множення.", di);
}

function мДваб(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове виключне або з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a ^ b;
  }
  var aXorFn = a["чародія_побітове_виключне_або"];
  if (aXorFn) {
    return мВикл(aXorFn, [b], di);
  }
  throw new Падіння("Неможливо виконати побітове виключне або.", di);
}

function мДвІ(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове і з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a & b;
  }
  var aAndFn = a["чародія_побітове_і"];
  if (aAndFn) {
    return мВикл(aAndFn, [b], di);
  }
  throw new Падіння("Неможливо виконати побітове і.", di);
}

function мДАбо(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове або з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a | b;
  }
  var aOrFn = a["чародія_побітове_або"];
  if (aOrFn) {
    return мВикл(aOrFn, [b], di);
  }
  throw new Падіння("Неможливо виконати побітове або.", di);
}

function мДні(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати побітове не з "пусто".`, di);
  }
  if (typeof a === "number") {
    return ~a;
  }
  var aNotFn = a["чародія_побітове_не"];
  if (aNotFn) {
    return мВикл(aNotFn, [], di);
  }
  throw new Падіння("Неможливо виконати побітове не.", di);
}

function мЗвлв(a, b, di) {
  if (a == null || b == 0) {
    throw new Падіння(`Неможливо виконати зсув вліво з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a << b;
  }
  var aShiftLeftFn = a["чародія_зсунути_вліво"];
  if (aShiftLeftFn) {
    return мВикл(aShiftLeftFn, [b], di);
  }
  throw new Падіння("Неможливо виконати зсув вліво.", di);
}

function мЗвпр(a, b, di) {
  if (a == null || b == 0) {
    throw new Падіння(`Неможливо виконати зсув вправо з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >> b;
  }
  var aShiftRightFn = a["чародія_зсунути_вправо"];
  if (aShiftRightFn) {
    return мВикл(aShiftRightFn, [b], di);
  }
  throw new Падіння("Неможливо виконати зсув вправо.", di);
}

function мЯк(a, di) {
  // todo
}

function мНегт(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати відʼємне значення з "пусто".`, di);
  }
  if (typeof a === "number") {
    return -a;
  }

  throw new Падіння("Неможливо отримати відʼємне значення.", di);
}

function мПозт(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати позитивне значення з "пусто".`, di);
  }
  if (typeof a === "number") {
    return +a;
  }
  throw new Падіння("Неможливо отримати позитивне значення.", di);
}

function мПдек(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати віднімання з "пусто".`, di);
  }
  if (typeof a === "number") {
    var value = a--;
    fn(a);
    return value;
  }
  throw new Падіння("Неможливо виконати віднімання.", di);
}

function мПінк(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "пусто".`, di);
  }
  if (typeof a === "number") {
    var value = a++;
    fn(a);
    return value;
  }
  throw new Падіння("Неможливо виконати додавання.", di);
}

function мПрдк(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "пусто".`, di);
  }
  if (typeof a === "number") {
    var value = --a;
    fn(value);
    return value;
  }
  throw new Падіння("Неможливо виконати додавання.", di);
}

function мПрік(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "пусто".`, di);
  }
  if (typeof a === "number") {
    var value = ++a;
    fn(value);
    return value;
  }
  throw new Падіння("Неможливо виконати додавання.", di);
}

function мМає(a, b, di) {
  if (a == null) {
    throw new Падіння("Неможливо перевірити чи містить з пустим значенням.", di);
  }
  var aContainsFn = a["чародія_перевірити_чи_містить"];
  if (aContainsFn) {
    return мВикл(aContainsFn, [b], di);
  }
  if (typeof a === "string") {
    if (typeof b === "string") {
      return a.includes(b);
    }
  }
  if (Array.isArray(a) || a instanceof Uint8Array) {
    return a.includes(b);
  }
  if (a instanceof Map) {
    return a.has(b);
  }
  return b in a;
}

function мОтрм(a, b, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати властивість "${b}" з "пусто".`, di);
  }
  if (a instanceof Map) {
    return a.get(b);
  }
  return a[b];
}

function мОтре(a, b, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати властивість "${b}" з "пусто".`, di);
  }
  if (a["чародія_отримати_спеціальну_властивість"]) {
    return мВикл(a["чародія_отримати_спеціальну_властивість"], [b], di);
  }
  if (a instanceof Map) {
    return a.get(b);
  }
  return a[b];
}

function мНі(a) {
  return !a;
}

function мРівн(a, b, di) {
  if (a == null && b == null) {
    return м_так;
  }
  if (a == null || b == null) {
    return м_ні;
  }
  if (typeof a === "number" && typeof b === "number") {
    return a === b ? м_так : м_ні;
  }
  if (typeof a === "string" && typeof b === "string") {
    return a === b ? м_так : м_ні;
  }
  if (typeof a === "boolean" && typeof b === "boolean") {
    return a === b ? м_так : м_ні;
  }
  if (a["чародія_порівняти_чи_рівно"]) {
    return мВикл(a["чародія_порівняти_чи_рівно"], [b], di);
  }
  return a === b ? м_так : м_ні;
}

function мЄ(a, b) {
  if (a == null && b == null) {
    return м_так;
  }
  if (a == null || b == null) {
    return м_ні;
  }
  if (b === Number && typeof a === "number") {
    return м_так;
  }
  if (b === String && typeof a === "string") {
    return м_так;
  }
  if (b === Boolean && typeof a === "boolean") {
    return м_так;
  }
  if (b === Map && a instanceof Map) {
    return м_так;
  }
  if (b === Array && Array.isArray(a)) {
    return м_так;
  }
  if (b === Function && typeof a === "function") {
    return м_так;
  }
  var structure = a[MAVKA]?.structure;
  while (structure) {
    if (structure === b) {
      return м_так;
    }
    structure = structure[MAVKA]?.parent;
  }
  return м_ні;
}

function мБілш(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи більше з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a > b;
  }
  if (a["чародія_порівняти_чи_більше"]) {
    return мВикл(a["чародія_порівняти_чи_більше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи більше.`, di);
}

function мМенш(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи менше з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a < b;
  }
  if (a["чародія_порівняти_чи_менше"]) {
    return мВикл(a["чародія_порівняти_чи_менше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи менше.`, di);
}

function мБірі(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи не менше з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >= b;
  }
  if (a["чародія_порівняти_чи_не_менше"]) {
    return мВикл(a["чародія_порівняти_чи_не_менше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи не менше з "пусто".`, di);
}

function мМері(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи не більше з "пусто".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a <= b;
  }
  if (a["чародія_порівняти_чи_не_більше"]) {
    return мВикл(a["чародія_порівняти_чи_не_більше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи не більше з "пусто".`, di);
}