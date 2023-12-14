class Падіння {
  constructor(значення, ді) {
    this.значення = значення;
    this.ді = ді;
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
    if (value[MAVKA].tdiia) {
      return `<дія ${value[MAVKA].name}>`;
    }
    if (value[MAVKA].tstructure) {
      return `<структура ${value[MAVKA].name}>`;
    }
    return "<обʼєкт>";
  }
  return "<портал>";
});
м_текст["чародія_перетворити_на_текст"] = мДія("чародія_перетворити_на_текст", [], function() {
  return "<структура текст>";
});
Object.defineProperty(м_текст.prototype, "довжина", {
  get() {
    return this.length;
  },
});
Object.defineProperty(м_текст.prototype, "символ", {
  get() {
    return мДія("символ", [], (args) => {
      return this.charAt(args[0] ?? args["позиція"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "код_символу", {
  get() {
    return мДія("код_символу", [], (args) => {
      return this.charCodeAt(args[0] ?? args["позиція"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "позиція", {
  get() {
    return мДія("позиція", [], (args) => {
      return this.indexOf(args[0] ?? args["позиція"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "повторити", {
  get() {
    return мДія("повторити", [], (args) => {
      return this.repeat(args[0] ?? args["кількість"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "замінити", {
  get() {
    return мДія("замінити", [], (args) => {
      return this.replaceAll(args[0] ?? args["старе_значення"], args[1] ?? args["нове_значення"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "замінити_перше", {
  get() {
    return мДія("замінити_перше", [], (args) => {
      return this.replace(args[0] ?? args["старе_значення"], args[1] ?? args["нове_значення"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "зрізати", {
  get() {
    return мДія("зрізати", [], (args) => {
      return this.substring(args[0] ?? args["від"], args[1] ?? args["до"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "приєднати", {
  get() {
    return мДія("приєднати", [], (args, di) => {
      var value = (args[0] ?? args["значення"])
        .map((v) => мВикл(м_текст.чародія_перетворити_на_текст, [v], di))
        .join("");
      return this.concat(value);
    });
  },
});
Object.defineProperty(м_текст.prototype, "розділити", {
  get() {
    return мДія("розділити", [], (args) => {
      return this.split(args[0] ?? args["роздільник"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "починається_з", {
  get() {
    return мДія("починається_з", [], (args) => {
      return this.startsWith(args[0] ?? args["значення"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "закінчується_на", {
  get() {
    return мДія("закінчується_на", [], (args) => {
      return this.endsWith(args[0] ?? args["значення"]);
    });
  },
});
Object.defineProperty(м_текст.prototype, "обрізати", {
  get() {
    return мДія("обрізати", [], () => {
      return this.trim();
    });
  },
});
Object.defineProperty(м_текст.prototype, "обтяти", {
  get() {
    return мДія("обтяти", [], () => {
      // todo: fix it
      var lineNumberWhereSmallestIndentationIs = 0;
      var lines = this.split("\n");
      var smallestIndentation = Infinity;
      for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        if (!line.trim()) {
          continue;
        }
        const indentation = line.match(/^\s*/)[0].length;
        if (indentation < smallestIndentation) {
          smallestIndentation = indentation;
          lineNumberWhereSmallestIndentationIs = i;
        }
      }
      const result = [];
      for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        if (!line.trim()) {
          continue;
        }
        result.push(line.slice(smallestIndentation));
      }
      return result.join("\n");
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
Object.defineProperty(м_список.prototype, "забрати", {
  get() {
    return мДія("забрати", [], () => {
      return this.pop();
    });
  },
});
Object.defineProperty(м_список.prototype, "отримати", {
  get() {
    return мДія("отримати", [], (args) => {
      return this[args[0] ?? args["позиція"]];
    });
  },
});
Object.defineProperty(м_список.prototype, "сортувати", {
  get() {
    return мДія("сортувати", [], (args, di) => {
      return this.sort((args[0] ?? args["д"]) ? (a, b) => мВикл(args[0] ?? args["д"], [a, b], di) : undefined);
    });
  },
});
Object.defineProperty(м_список.prototype, "фільтрувати", {
  get() {
    return мДія("фільтрувати", [], (args, di) => {
      return this.filter((a) => мВикл(args[0] ?? args["д"], [a], di));
    });
  },
});
Object.defineProperty(м_список.prototype, "знайти", {
  get() {
    return мДія("знайти", [], (args, di) => {
      return this.find((a) => мВикл(args[0] ?? args["д"], [a], di));
    });
  },
});
Object.defineProperty(м_список.prototype, "знайти_позицію", {
  get() {
    return мДія("знайти_позицію", [], (args, di) => {
      return this.findIndex((a) => мВикл(args[0] ?? args["д"], [a], di));
    });
  },
});
Object.defineProperty(м_список.prototype, "перетворити", {
  get() {
    return мДія("перетворити", [], (args, di) => {
      return this.map((a) => мВикл(args[0] ?? args["д"], [a], di));
    });
  },
});
Object.defineProperty(м_список.prototype, "заповнити", {
  get() {
    return мДія("заповнити", [], (args) => {
      return this.fill(args[0] ?? args["значення"]);
    });
  },
});
Object.defineProperty(м_список.prototype, "злити", {
  get() {
    return мДія("злити", [], (args) => {
      return this.concat(args[0] ?? args["значення"]);
    });
  },
});
Object.defineProperty(м_список.prototype, "зʼєднати", {
  get() {
    return мДія("зʼєднати", [], (args, di) => {
      return this.map((v) => мВикл(м_текст.чародія_перетворити_на_текст, [v], di)).join(args[0] ?? args["роздільник"]);
    });
  },
});
Object.defineProperty(м_список.prototype, "обернути", {
  get() {
    return мДія("обернути", [], () => {
      return this.reverse();
    });
  },
});
Object.defineProperty(м_список.prototype, "зрізати", {
  get() {
    return мДія("зрізати", [], (args) => {
      return this.slice(args[0] ?? args["від"], args[1] ?? args["до"]);
    });
  },
});
Object.defineProperty(м_список.prototype, "скоротити", {
  get() {
    return мДія("скоротити", [], (args, di) => {
      return this.reduce((a, b) => мВикл(args[0] ?? args["д"], [a, b], di), args[1] ?? args["початкове_значення"]);
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

function мТипТ(value) {
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

function __мГТкс__(...args) {
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
    if (v[MAVKA]) {
      if (v[MAVKA].tdiia) {
        return `<дія ${v[MAVKA].name}>`;
      }
      if (v[MAVKA].tstructure) {
        return `<структура ${v[MAVKA].name}>`;
      }
      if (v[MAVKA].structure) {
        const entries = Object.entries(v).map(([k, v]) => `${convert(k, depth + 1)}=${convert(v, depth + 1)}`);
        return `${v[MAVKA].structure[MAVKA].name}(${entries})`;
      }
    }
    return "<портал>";
  };
  return args.map((v) => convert(v, 0)).join(" ");
}

if (typeof window !== "undefined") {
  window.__мГТкс__ = __мГТкс__;
} else if (typeof global !== "undefined") {
  global.__мГТкс__ = __мГТкс__;
}

function мДія(name, params, fn) {
  var diiaValue = function(...args) {
    return fn(args);
  };
  diiaValue[MAVKA] = Object.create(null);
  diiaValue[MAVKA].tdiia = true;
  diiaValue[MAVKA].name = name;
  diiaValue[MAVKA].params = params;
  diiaValue[MAVKA].perform = fn;
  return diiaValue;
}

function мСтрк(name, params, parent, di) {
  var structureValue = Object.create(null);
  structureValue[MAVKA] = Object.create(null);
  structureValue[MAVKA].tstructure = true;
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
    throw new Падіння(`Неможливо змінити властивіть "${name}" для "${мТипТ(a)}".`, di);
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
    throw new Падіння(`Неможливо перебрати "${мТипТ(value)}".`, di);
  }
  if (value[Symbol.iterator]) {
    return value;
  }
  throw new Падіння(`Неможливо перебрати "${мТипТ(value)}".`, di);
}

function мІтерП(value, di) {
  if (value == null) {
    throw new Падіння(`Неможливо перебрати "${мТипТ(value)}".`, di);
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
    throw new Падіння(`Неможливо встановити спеціальну властивість для "${мТипТ(a)}".`, di);
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
    throw new Падіння(`Неможливо виконати "${мТипТ(value)}".`, di);
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
  throw new Падіння(`Неможливо виконати "${мТипТ(value)}".`, di);
}

function мДодт(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
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
  throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
}

function мВідн(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати віднімання з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a - b;
  }
  var aSubtractFn = a["чародія_відняти"];
  if (aSubtractFn) {
    return мВикл(aSubtractFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати віднімання з "${мТипТ(a)}".`, di);
}

function мМнож(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати множення з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a * b;
  }
  var aMultiplyFn = a["чародія_помножити"];
  if (aMultiplyFn) {
    return мВикл(aMultiplyFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати множення з "${мТипТ(a)}".`, di);
}

function мДілт(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a / b;
  }
  var aDivideFn = a["чародія_поділити"];
  if (aDivideFn) {
    return мВикл(aDivideFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати ділення з "${мТипТ(a)}".`, di);
}

function мОстч(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення за модулем остача з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a % b;
  }
  var aModFn = a["чародія_поділити_за_модулем_остача"];
  if (aModFn) {
    return мВикл(aModFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати ділення за модулем остача з "${мТипТ(a)}".`, di);
}

function мСтпн(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати піднесення до степеня з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return Math.pow(a, b);
  }
  var aDivDivFn = a["чародія_піднести_до_степеня"];
  if (aDivDivFn) {
    return мВикл(aDivDivFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати піднесення до степеня з "${мТипТ(a)}".`, di);
}

function мОст2(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати ділення за модулем частка з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return Math.floor(a / b);
  }
  var aDivDivFn = a["чародія_поділити_за_модулем_частка"];
  if (aDivDivFn) {
    return мВикл(aDivDivFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати ділення за модулем частка з "${мТипТ(a)}".`, di);
}

function мДваб(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове виключне або з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a ^ b;
  }
  var aXorFn = a["чародія_побітове_виключне_або"];
  if (aXorFn) {
    return мВикл(aXorFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати побітове виключне або з "${мТипТ(a)}".`, di);
}

function мДвІ(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове і з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a & b;
  }
  var aAndFn = a["чародія_побітове_і"];
  if (aAndFn) {
    return мВикл(aAndFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати побітове і з "${мТипТ(a)}".`, di);
}

function мДАбо(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо виконати побітове або з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a | b;
  }
  var aOrFn = a["чародія_побітове_або"];
  if (aOrFn) {
    return мВикл(aOrFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати побітове або з "${мТипТ(a)}".`, di);
}

function мДні(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати побітове не з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    return ~a;
  }
  var aNotFn = a["чародія_побітове_не"];
  if (aNotFn) {
    return мВикл(aNotFn, [], di);
  }
  throw new Падіння(`Неможливо виконати побітове не з "${мТипТ(a)}".`, di);
}

function мЗвлв(a, b, di) {
  if (a == null || b == 0) {
    throw new Падіння(`Неможливо виконати зсув вліво з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a << b;
  }
  var aShiftLeftFn = a["чародія_зсунути_вліво"];
  if (aShiftLeftFn) {
    return мВикл(aShiftLeftFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати зсув вліво з "${мТипТ(a)}".`, di);
}

function мЗвпр(a, b, di) {
  if (a == null || b == 0) {
    throw new Падіння(`Неможливо виконати зсув вправо з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >> b;
  }
  var aShiftRightFn = a["чародія_зсунути_вправо"];
  if (aShiftRightFn) {
    return мВикл(aShiftRightFn, [b], di);
  }
  throw new Падіння(`Неможливо виконати зсув вправо з "${мТипТ(a)}".`, di);
}

function мЯк(a, di) {
  // todo
}

function мНегт(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати відʼємне значення з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    return -a;
  }

  throw new Падіння(`Неможливо отримати відʼємне значення з "${мТипТ(a)}".`, di);
}

function мПозт(a, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати позитивне значення з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    return +a;
  }
  throw new Падіння(`Неможливо отримати позитивне значення з "${мТипТ(a)}".`, di);
}

function мПдек(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати віднімання з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    var value = a--;
    fn(a);
    return value;
  }
  throw new Падіння(`Неможливо виконати віднімання з "${мТипТ(a)}".`, di);
}

function мПінк(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    var value = a++;
    fn(a);
    return value;
  }
  throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
}

function мПрдк(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    var value = --a;
    fn(value);
    return value;
  }
  throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
}

function мПрік(a, fn, di) {
  if (a == null) {
    throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number") {
    var value = ++a;
    fn(value);
    return value;
  }
  throw new Падіння(`Неможливо виконати додавання з "${мТипТ(a)}".`, di);
}

function мМає(a, b, di) {
  if (a == null) {
    throw new Падіння(`Неможливо перевірити чи містить з "${мТипТ(a)}".`, di);
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
    throw new Падіння(`Неможливо отримати властивість "${b}" з "${мТипТ(a)}".`, di);
  }
  if (a instanceof Map) {
    return a.get(b);
  }
  return a[b];
}

function мОтре(a, b, di) {
  if (a == null) {
    throw new Падіння(`Неможливо отримати властивість "${b}" з "${мТипТ(a)}".`, di);
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
    throw new Падіння(`Неможливо порівняти чи більше з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a > b;
  }
  if (a["чародія_порівняти_чи_більше"]) {
    return мВикл(a["чародія_порівняти_чи_більше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи більше з "${мТипТ(a)}".`, di);
}

function мМенш(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи менше з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a < b;
  }
  if (a["чародія_порівняти_чи_менше"]) {
    return мВикл(a["чародія_порівняти_чи_менше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи менше з "${мТипТ(a)}".`, di);
}

function мБірі(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи не менше з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a >= b;
  }
  if (a["чародія_порівняти_чи_не_менше"]) {
    return мВикл(a["чародія_порівняти_чи_не_менше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи не менше з "${мТипТ(a)}".`, di);
}

function мМері(a, b, di) {
  if (a == null || b == null) {
    throw new Падіння(`Неможливо порівняти чи не більше з "${мТипТ(a)}".`, di);
  }
  if (typeof a === "number" && typeof b === "number") {
    return a <= b;
  }
  if (a["чародія_порівняти_чи_не_більше"]) {
    return мВикл(a["чародія_порівняти_чи_не_більше"], [b], di);
  }
  throw new Падіння(`Неможливо порівняти чи не більше з "${мТипТ(a)}".`, di);
}