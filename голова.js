var MAVKA = Symbol("мавка");

function мДія(name, params = new Map(), fn) {
    var diiaValue = function (...args) {
        return diiaValue[MAVKA].perform(args);
    }
    diiaValue[MAVKA] = Object.create(null);
    diiaValue[MAVKA].name = name;
    diiaValue[MAVKA].params = params;
    diiaValue[MAVKA].perform = fn;
    return diiaValue;
}


function мПарм(name, type, defaultValue) {
    return new Map([
        ["назва", name],
        ["тип", type],
        ["значення", defaultValue]
    ]);
}

function мВикл(value, args) {
    if (value == null) {
        throw new Error(`Неможливо виконати "пусто".`);
    }
    var valueCallFn = value["чародія_викликати"];
    if (valueCallFn) {
        return мВикл(valueCallFn, args);
    }
    var valueMavkaValue = value[MAVKA];
    if (valueMavkaValue) {
        var valueMavkaValuePerform = valueMavkaValue.perform;
        if (valueMavkaValuePerform) {
            return valueMavkaValuePerform(args);
        }
    }
    throw new Error("Неможливо виконати.");
}

function мДодт(a, b) {
    if (typeof a === "number" && typeof b === "number") {
        return a + b;
    }
    if (typeof a === "string" && typeof b === "string") {
        return a + b;
    }
    var aSubtractFn = a["чародія_додати"];
    if (aSubtractFn) {
        return мВикл(aSubtractFn, [b]);
    }
    throw new Error("Неможливо виконати віднімання.");
}

function мВідн(a, b) {
    if (typeof a === "number" && typeof b === "number") {
        return a - b;
    }
    var aSubtractFn = a["чародія_відняти"];
    if (aSubtractFn) {
        return мВикл(aSubtractFn, [b]);
    }
    throw new Error("Неможливо виконати віднімання.");
}

function мОтрм(a, b) {
    if (a == null) {
        throw new Error(`Неможливо отримати властивість "${b}" з "пусто".`);
    }
    return a[b];
}


// // OLD!!!!
//
// class MavkaError {
//     constructor(value, di) {
//         this.value = value;
//         this.di = di;
//     }
// }
//
// var mavka_utf8Decoder = new TextDecoder("utf-8");
// var mavka_utf8Encoder = new TextEncoder("utf-8");
//
// var м_обʼєкт = Object;
// var м_пусто = null;
// var м_так = true;
// var м_ні = false;
// var м_логічне = Boolean;
// var м_число = Number;
// var м_текст = String;
// var м_список = Array;
// var м_словник = Map;
// var м_Дія = Function;
// var м_Структура;
// var м_Модуль;
// var м_байти = Uint8Array;
// var м_безкрай = Infinity;
// var м_нечисло = NaN;
//
// Object.__m_name__ = "обʼєкт";
// Object.__m_props__ = Object.create(null);
//
// Boolean.__m_name__ = "логічне";
// Boolean.__m_props__ = Object.create(null);
// Boolean.prototype.__m_type__ = "logical";
//
// Number.__m_name__ = "число";
// Number.__m_props__ = Object.create(null);
// Number.prototype.__m_type__ = "number";
//
// String.__m_name__ = "текст";
// String.__m_props__ = Object.create(null);
// String.prototype.__m_type__ = "text";
//
// Array.__m_name__ = "список";
// Array.__m_props__ = Object.create(null);
// Array.prototype.__m_type__ = "list";
//
// Function.__m_name__ = "Дія";
// Function.__m_props__ = Object.create(null);
// Function.__m_props__["назва"] = (args, di) => {
//     const value = mavka_arg(args, 0, "значення", м_Дія, undefined, di);
//     return value.__m_name__;
// };
// Function.__m_props__["виконати"] = (args, di) => {
//     const value = mavka_arg(args, 0, "значення", м_Дія, undefined, di);
//     const valueArgs = mavka_arg(args, 1, "аргументи", [м_список, м_словник], undefined, di);
//     if (mavka_compare_is(valueArgs, м_словник)) {
//         return value(Object.fromEntries(valueArgs.entries()), di);
//     }
//     return value(valueArgs, di);
// };
//
// Map.__m_name__ = "словник";
// Map.__m_props__ = Object.create(null);
// Map.prototype.__m_type__ = "dictionary";
// Map.__m_props__["розмір"] = (args, di) => {
//     const value = mavka_arg(args, 0, "значення", м_словник, undefined, di);
//     return value.size;
// };
//
// м_Структура = Object.create(null);
// м_Структура.__m_name__ = "Структура";
// м_Структура.__m_props__ = Object.create(null);
// м_Структура.__m_props__["дізнатись"] = (args, di) => {
//     const value = mavka_arg(args, 0, "значення", undefined, undefined, di);
//     if (value == null) {
//         return null;
//     }
//     switch (value.__m_type__) {
//         case "logical":
//             return м_логічне;
//         case "number":
//             return м_число;
//         case "text":
//             return м_текст;
//         case "list":
//             return м_список;
//         case "diia":
//             return м_Дія;
//         case "dictionary":
//             return м_словник;
//         case "bytes":
//             return м_байти;
//         case "object":
//             return value.__m_structure__;
//         default:
//             return null;
//     }
// };
//
// м_Модуль = Object.create(null);
// м_Модуль.__m_props__ = Object.create(null);
//
// Uint8Array.__m_name__ = "байти";
// Uint8Array.__m_props__ = Object.create(null);
// Uint8Array.prototype.__m_type__ = "bytes";
//
// var mavka_to_boolean = (value, di) => {
//     if (value == null) {
//         return false;
//     }
//     if (value.__m_props__ && value.__m_props__["чародія_перетворення_на_логічне"]) {
//         return value.__m_props__["чародія_перетворення_на_логічне"]();
//     }
//     return Boolean(value);
// };
//
// var mavka_to_number = (value, di) => {
//     if (value == null) {
//         return 0;
//     }
//     if (value.__m_props__ && value.__m_props__["чародія_перетворення_на_число"]) {
//         return value.__m_props__["чародія_перетворення_на_число"]();
//     }
//     if (value.__m_type__ === "number") {
//         return value;
//     }
//     if (value.__m_type__ === "text") {
//         return Number(value);
//     }
//     throw new MavkaError("Неможливо перетворити на число.", di);
// };
//
// var mavka_to_string = (value, di) => {
//     if (value == null) {
//         return "пусто";
//     }
//     if (value.__m_props__ && value.__m_props__["чародія_перетворення_на_текст"]) {
//         return value.__m_props__["чародія_перетворення_на_текст"]();
//     }
//     switch (value.__m_type__) {
//         case "logical":
//             return value ? "так" : "ні";
//         case "number":
//             if (value === Infinity) {
//                 return "безкрай";
//             }
//             if (Number.isNaN(value)) {
//                 return "неч";
//             }
//             return value.toString();
//         case "text":
//             return value;
//         case "bytes":
//             return mavka_utf8Decoder.decode(value);
//         default:
//             throw new MavkaError("Неможливо перетворити на текст.", di);
//     }
// };
//
// var mavka_get_type_name = (value) => {
//     if (value == null) {
//         return "пусто";
//     }
//     switch (value.__m_type__) {
//         case "logical":
//             return "логічне";
//         case "number":
//             return "число";
//         case "text":
//             return "текст";
//         case "list":
//             return "список";
//         case "diia":
//             return "Дія";
//         case "god":
//             return "бог";
//         case "dictionary":
//             return "словник";
//         case "object":
//             return value.__m_structure__.__m_name__;
//         case "structure":
//             return "Структура";
//         case "module":
//             return value.__m_name__;
//         case "portal":
//             return "портал";
//         default:
//             return "<невідомий тип>";
//     }
// };
//
// var mavka_to_pretty_string = (value, root = true) => {
//     if (value == null) {
//         return "пусто";
//     }
//     if (value.__m_type__ === "logical") {
//         return value ? "так" : "ні";
//     }
//     if (value.__m_type__ === "number") {
//         if (value === Infinity) {
//             return "безкрай";
//         }
//         if (Number.isNaN(value)) {
//             return "неч";
//         }
//         return value.toString();
//     }
//     if (value.__m_type__ === "text") {
//         if (root) {
//             return value;
//         }
//         return `"${value}"`;
//     }
//     if (value.__m_type__ === "diia") {
//         if (value.__m_name__) {
//             return `<дія ${value.__m_name__}>`;
//         } else {
//             return `<дія>`;
//         }
//     }
//     if (value.__m_type__ === "list") {
//         return "[" + value.map((v) => mavka_to_pretty_string(v, false)).join(", ") + "]";
//     }
//     if (value.__m_type__ === "god") {
//         const elementConstructors = value.__m_elements__.map((el) => {
//             if (el.__m_type__ === "logical") {
//                 return "логічне";
//             }
//             if (el.__m_type__ === "number") {
//                 return "число";
//             }
//             if (el.__m_type__ === "text") {
//                 return "текст";
//             }
//             if (el.__m_type__ === "list") {
//                 return "список";
//             }
//             if (el.__m_type__ === "diia") {
//                 return "Дія";
//             }
//             if (el.__m_type__ === "god") {
//                 return "бог";
//             }
//             if (el.__m_type__ === "dictionary") {
//                 return "словник";
//             }
//             if (el.__m_type__ === "structure") {
//                 return "Структура";
//             }
//             if (el.__m_type__ === "object") {
//                 return el.__m_structure__.__m_name__;
//             }
//             return "пусто";
//         });
//         return `<бог [${elementConstructors.join(", ")}]>`;
//     }
//     if (value.__m_type__ === "module") {
//         var moduleKeys = Object.keys(value.__m_props__);
//         return `<модуль ${value.__m_name__}[${moduleKeys.join(", ")}]>`;
//     }
//     if (value.__m_type__ === "structure") {
//         return `<структура ${value.__m_name__}>`;
//     }
//     if (value.__m_type__ === "dictionary") {
//         const entries = [];
//         for (const [k, v] of value) {
//             entries.push(`${mavka_to_pretty_string(k, false)}=${mavka_to_pretty_string(v, false)}`);
//         }
//         return `(${entries.join(", ")})`;
//     }
//     if (value.__m_type__ === "object") {
//         const entries = [];
//         for (const k in value.__m_structure__.__m_params__) {
//             entries.push(`${k}=${mavka_to_pretty_string(value.__m_props__[k], false)}`);
//         }
//         return `${value.__m_structure__.__m_name__}(${entries.join(", ")})`;
//     }
//     if (value.__m_type__ === "portal") {
//         return `<портал>`;
//     }
//     if (value.__m_type__ === "bytes") {
//         return `<байти ${value.length}>`;
//     }
//     return "<невідоме значення>";
// };
//
// var mavka_mapReturn = (value, type, di) => {
//     if (!mavka_compare_is(value, type, di)) {
//         throw new MavkaError("Невірний тип результату.", di);
//     }
//     return value;
// };
//
// // as
// var mavka_do_as = (value, type, di) => {
//     if (value && value.__m_type__ === "god") {
//         const el = value.__m_elements__.find((el) => mavka_compare_is(el, type, di));
//         if (el) {
//             return el;
//         }
//         throw new MavkaError("Неможливо отримати бога як todo.", di);
//     }
//     throw new MavkaError("Неможливо перетворити значення.", di);
// };
//
// var mavka_portal = (value) => {
//     if (value == null) {
//         return null;
//     }
//
//     switch (typeof value) {
//         case "string":
//             return value;
//         case "number":
//             return value;
//         case "boolean":
//             return value;
//         case "function":
//             return value;
//         default:
//             if (Array.isArray(value)) {
//                 return value;
//             }
//
//             if (value.__m_type__) {
//                 return value;
//             }
//
//             var objectProxy = function (obj) {
//                 var object = Object.create(null);
//                 object.__m_type__ = "portal";
//                 object.__m_props__ = new Proxy(obj, {
//                     get(target, prop, receiver) {
//                         if (prop in target) {
//                             return mavka_portal(target[prop]);
//                         }
//                         return null;
//                     },
//                     set(target, prop, value, receiver) {
//                         if (value != null && value.__m_type__ === "object") {
//                             target[prop] = value.__m_props__;
//                         } else {
//                             target[prop] = value;
//                         }
//                         return true;
//                     }
//                 });
//                 return object;
//             };
//
//             return objectProxy(value);
//     }
// };
//
// var mavka_spread = (value, di) => {
//     if (Array.isArray(value)) {
//         return value;
//     }
//     if (value.__m_type__ === "dictionary") {
//         return Array.from(value.values());
//     }
//     throw new MavkaError("Неможливо розгорнути значення.", di);
// };
//
// var mavka_entries = (value, di) => {
//     if (value == null) {
//         throw new MavkaError("Неможливо отримати ітератор.", di);
//     }
//     if (value.__m_type__ === "list") {
//         return value.entries();
//     }
//     if (value.__m_type__ === "dictionary") {
//         return value.entries();
//     }
//     if (value.__m_type__ === "object") {
//         return Object.entries(value.__m_props__);
//     }
//     throw new MavkaError("Неможливо отримати ітератор.", di);
// };
//
// var mavka_values = (value, di) => {
//     if (value == null) {
//         throw new MavkaError("Неможливо отримати ітератор.", di);
//     }
//     if (value.__m_type__ === "list") {
//         return value;
//     }
//     if (value.__m_type__ === "dictionary") {
//         return value.values();
//     }
//     if (value.__m_type__ === "object") {
//         return Object.values(value.__m_props__);
//     }
//     throw new MavkaError("Неможливо отримати ітератор.", di);
// };
//
// var м_Помилка = mavka_structure(
//     "Помилка",
//     null,
//     {
//         "повідомлення": mavka_param(0, м_текст, "")
//     }
// );
//
// function mavka_diia(name, params, fn, result, di) {
//     var diia = function (...args) {
//         return diia.__m_call__(args);
//     };
//     diia.__m_call__ = function (args, di) {
//         var arg = function (argName) {
//             return mavka_arg(
//                 args,
//                 diia.__m_params__[argName].get("позиція"),
//                 argName,
//                 diia.__m_params__[argName].get("тип"),
//                 diia.__m_params__[argName].get("значення"),
//                 di
//             );
//         };
//         return fn(args, di, {arg});
//     };
//     diia.__m_name__ = name;
//     diia.__m_params__ = params;
//     diia.__m_type__ = "diia";
//     return diia;
// }
//
// function mavka_method(params, fn, result, di) {
//     var method = function (me, args, di) {
//         var arg = function (argName) {
//             return mavka_arg(
//                 args,
//                 method.__m_params__[argName].get("позиція"),
//                 argName,
//                 method.__m_params__[argName].get("тип"),
//                 method.__m_params__[argName].get("значення"),
//                 di
//             );
//         };
//         return fn(me, args, di, {arg});
//     };
//     method.__m_params__ = params;
//     return method;
// }
//
// function mavka_param(index, type, defaultValue) {
//     return new Map([
//         ["позиція", index],
//         ["тип", type],
//         ["значення", defaultValue]
//     ]);
// }
//
// function mavka_arg(args, index, name, type, defaultValue, di) {
//     var value = Array.isArray(args) ? args[index] : args[name];
//     if (type === undefined) {
//         if (defaultValue === undefined) {
//             return value === undefined ? null : value;
//         } else {
//             return value === undefined ? defaultValue : value;
//         }
//     }
//     if (value === undefined) {
//         if (defaultValue === undefined) {
//             throw new MavkaError(`Не вистачає аргумента "${name}".`, di);
//         } else {
//             return defaultValue;
//         }
//     }
//     if (Array.isArray(type)) {
//         // todo: implement
//     } else {
//         if (type) {
//             if (type.__m_type__ === "structure") {
//                 if (value != null) {
//                     if (value.__m_type__ === "dictionary") {
//                         return mavka_call(type, Object.fromEntries(value.entries()), di);
//                     }
//                 }
//             }
//             if (!mavka_compare_is(value, type, di)) {
//                 throw new MavkaError(`Очікується, що "${name}" буде "${type.__m_name__}", отримано "${mavka_get_type_name(value)}".`, di);
//             }
//         } else {
//             if (value !== null) {
//                 throw new MavkaError(`Очікується, що "${name}" буде "пусто", отримано "${mavka_get_type_name(value)}".`, di);
//             }
//         }
//     }
//     return value;
// }
//
// function mavka_add(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати додавання з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_додати"]) {
//         return a.__m_props__["чародія_додати"]([b], di);
//     }
//     if (a.__m_type__ === "text" || b.__m_type__ === "text") {
//         return a + b;
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a + b;
//     }
//     throw new MavkaError("Неможливо виконати додавання.", di);
// }
//
// function mavka_sub(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати віднімання з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_відняти"]) {
//         return a.__m_props__["чародія_відняти"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a - b;
//     }
//     throw new MavkaError("Неможливо виконати віднімання.", di);
// }
//
// function mavka_mul(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати множення з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_помножити"]) {
//         return a.__m_props__["чародія_помножити"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a * b;
//     }
//     throw new MavkaError("Неможливо виконати множення.", di);
// }
//
// function mavka_div(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати ділення з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_поділити"]) {
//         return a.__m_props__["чародія_поділити"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a / b;
//     }
//     throw new MavkaError("Неможливо виконати ділення: ", di);
// }
//
// function mavka_mod(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати ділення за модулем остача з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_поділити_за_модулем_остача"]) {
//         return a.__m_props__["чародія_поділити_за_модулем_остача"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a % b;
//     }
//     throw new MavkaError("Неможливо виконати ділення за модулем остача.", di);
// }
//
// function mavka_divDiv(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати ділення за модулем частка з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_поділити_за_модулем_частка"]) {
//         return a.__m_props__["чародія_поділити_за_модулем_частка"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return Math.floor(a / b);
//     }
//     throw new MavkaError("Неможливо виконати ділення за модулем частка.", di);
// }
//
// function mavka_pow(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати піднесення до степеня з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_піднести_до_степеня"]) {
//         return a.__m_props__["чародія_піднести_до_степеня"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a ** b;
//     }
//     throw new MavkaError("Неможливо виконати піднесення до степеня.", di);
// }
//
// function mavka_shiftLeft(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати зсув вліво з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_зсунути_вліво"]) {
//         return a.__m_props__["чародія_зсунути_вліво"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a << b;
//     }
//     throw new MavkaError("Неможливо виконати зсув вліво.", di);
// }
//
// function mavka_shiftRight(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати зсув вправо з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_зсунути_вправо"]) {
//         return a.__m_props__["чародія_зсунути_вправо"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a >> b;
//     }
//     throw new MavkaError("Неможливо виконати зсув вправо.", di);
// }
//
// function mavka_bitAnd(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати побітове і з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_побітове_і"]) {
//         return a.__m_props__["чародія_побітове_і"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a & b;
//     }
//     throw new MavkaError("Неможливо виконати побітове і.", di);
// }
//
// function mavka_bitOr(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати побітове або з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_побітове_або"]) {
//         return a.__m_props__["чародія_побітове_або"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a | b;
//     }
//     throw new MavkaError("Неможливо виконати побітове або.", di);
// }
//
// function mavka_bitNot(a, di) {
//     if (a == null) {
//         throw new MavkaError("Неможливо виконати побітове не з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_побітове_не"]) {
//         return a.__m_props__["чародія_побітове_не"]();
//     }
//     if (a.__m_type__ === "number") {
//         return ~a;
//     }
//     throw new MavkaError("Неможливо виконати побітове не.", di);
// }
//
// function mavka_bitXor(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо виконати побітове виключне або з \"пусто\".", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_побітове_виключне_або"]) {
//         return a.__m_props__["чародія_побітове_виключне_або"]([b], di);
//     }
//     if (a.__m_type__ === "number" && b.__m_type__ === "number") {
//         return a ^ b;
//     }
//     throw new MavkaError("Неможливо виконати побітове виключне або.", di);
// }
//
// function mavka_positive(a, di) {
//     if (a == null) {
//         throw new MavkaError("Неможливо отримати позитивне значення з \"пусто\".", di);
//     }
//     if (a.__m_type__ === "number") {
//         return +a;
//     }
//     throw new MavkaError("Неможливо отримати позитивне значення.", di);
// }
//
// function mavka_negative(a, di) {
//     if (a == null) {
//         throw new MavkaError("Неможливо отримати відʼємне значення з \"пусто\".", di);
//     }
//     if (a.__m_type__ === "number") {
//         return -a;
//     }
//     throw new MavkaError("Неможливо отримати відʼємне значення.", di);
// }
//
// // todo: optimize
//
// function mavka_call(a, args = [], di = undefined) {
//     if (a == null) {
//         throw new MavkaError("Неможливо виконати \"пусто\".", di);
//     }
//     if (a === м_логічне) {
//         return mavka_to_boolean(mavka_arg(args, 0, "значення"), di);
//     }
//     if (a === м_число) {
//         return mavka_to_number(mavka_arg(args, 0, "значення"), di);
//     }
//     if (a === м_текст) {
//         return mavka_to_string(mavka_arg(args, 0, "значення"), di);
//     }
//     if (a === м_список) {
//         return [];
//     }
//     if (a === м_байти) {
//         var argValue = mavka_arg(args, 0, "значення", [м_число]);
//         var bytesObject;
//         if (mavka_compare_is(argValue, м_число, di)) {
//             bytesObject = new Uint8Array(argValue);
//         } else if (mavka_compare_is(argValue, м_текст, di)) {
//             bytesObject = mavka_utf8Encoder.encode(argValue);
//         } else {
//             throw new MavkaError("Неможливо створити байти.", di);
//         }
//         return bytesObject;
//     }
//     if (a === м_словник) {
//         var dictMap = new Map();
//         if (Array.isArray(args)) {
//             for (let i = 0; i < args.length; i++) {
//                 dictMap.set(i, args[i]);
//             }
//         } else {
//             for (const [k, v] of Object.entries(args)) {
//                 dictMap.set(k, v);
//             }
//         }
//         return dictMap;
//     }
//     if (a === м_Дія) {
//         throw new MavkaError("Неможливо виконати.", di);
//     }
//     if (a === м_Структура) {
//         throw new MavkaError("Неможливо виконати.", di);
//     }
//     if (a === м_Модуль) {
//         throw new MavkaError("Неможливо виконати.", di);
//     }
//     if (a.__m_type__ === "diia") {
//         return a.__m_call__(args, di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_викликати"]) {
//         return a.__m_props__["чародія_викликати"].__m_call__(args, di);
//     }
//     throw new MavkaError(`Неможливо виконати "${mavka_get_type_name(a)}".`, di);
// }
//
// // todo: optimize
//
// function mavka_compare_eq(a, b, di) {
//     if (a === b) {
//         return true;
//     }
//     if (a == null && b == null) {
//         return true;
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_порівняти_чи_рівно"]) {
//         return a.__m_props__["чародія_порівняти_чи_рівно"]([b], di);
//     }
//     return false;
// }
//
// function mavka_compare_lt(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо порівняти з пустим значенням.", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_порівняти_чи_менше"]) {
//         return a.__m_props__["чародія_порівняти_чи_менше"]([b], di);
//     }
//     return a < b;
// }
//
// function mavka_compare_gt(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо порівняти з пустим значенням.", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_порівняти_чи_більше"]) {
//         return a.__m_props__["чародія_порівняти_чи_більше"]([b], di);
//     }
//     return a > b;
// }
//
// function mavka_compare_le(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо порівняти з пустим значенням.", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_порівняти_чи_не_більше"]) {
//         return a.__m_props__["чародія_порівняти_чи_не_більше"]([b], di);
//     }
//     return a <= b;
// }
//
// function mavka_compare_ge(a, b, di) {
//     if (a == null || b == null) {
//         throw new MavkaError("Неможливо порівняти з пустим значенням.", di);
//     }
//     if (a.__m_props__ && a.__m_props__["чародія_порівняти_чи_не_менше"]) {
//         return a.__m_props__["чародія_порівняти_чи_не_менше"]([b], di);
//     }
//     return a >= b;
// }
//
// function mavka_compare_is(a, b, di) {
//     if (a == null && b == null) {
//         return true;
//     }
//     if (a == null && b != null) {
//         return false;
//     }
//     if (a != null && b == null) {
//         return false;
//     }
//     if (a.__m_type__ === "number") {
//         return b === м_число;
//     }
//     if (a.__m_type__ === "text") {
//         return b === м_текст;
//     }
//     if (a.__m_type__ === "logical") {
//         return b === м_логічне;
//     }
//     if (a.__m_type__ === "list") {
//         return b === м_список;
//     }
//     if (a.__m_type__ === "diia") {
//         return b === м_Дія;
//     }
//     if (a.__m_type__ === "dictionary") {
//         return b === м_словник;
//     }
//     if (a.__m_type__ === "bytes") {
//         return b === м_байти;
//     }
//     if (a.__m_type__ === "god") {
//         return a.__m_elements__.some((el) => mavka_compare_is(el, b, di));
//     }
//     if (a.__m_type__ === "object") {
//         if (a.__m_structure__ === b) {
//             return true;
//         }
//         let parent = a.__m_structure__.__m_parent__;
//         while (parent) {
//             if (parent === b) {
//                 return true;
//             }
//             parent = parent.__m_parent__;
//         }
//         return false;
//     }
//     throw new MavkaError("[BUG] невідоме значення для порівняння: " + a.__m_type__, di);
// }
//
// function mavka_compare_contains(a, b, di) {
//     if (a == null) {
//         throw new MavkaError("Неможливо перевірити чи містить з пустим значенням.", di);
//     }
//     if (a.__m_type__ === "text") {
//         if (b && b.__m_type__ === "text") {
//             return a.includes(b);
//         }
//     }
//     if (a.__m_type__ === "list" || a.__m_type__ === "bytes") {
//         return a.includes(b);
//     }
//     if (a.__m_type__ === "dictionary") {
//         return a.has(b);
//     }
//     if (a.__m_type__ === "object") {
//         if (b && b.__m_type__ === "text") {
//             return b in a.__m_props__;
//         }
//     }
//     throw new MavkaError("Неможливо перевірити чи містить.", di);
// }
//
// var not = function (a, di) {
//     return !mavka_to_boolean(a, di);
// };
//
// // todo: optimize
//
// function mavka_commonGet_bytes(a, b, di) {
//     if (b.__m_type__ === "number") {
//         return a[b];
//     } else {
//         if (b === "довжина") {
//             return a.length;
//         }
//         if (b === "заповнити") {
//             return mavka_diia(
//                 "заповнити",
//                 {
//                     "значення": mavka_param(0, "значення")
//                 },
//                 function (args, di, {arg}) {
//                     return a.fill(arg("значення"));
//                 }
//             );
//         }
//         if (b === "обернути") {
//             return mavka_diia(
//                 "обернути",
//                 {},
//                 function () {
//                     return a.reverse();
//                 }
//             );
//         }
//         if (b === "зрізати") {
//             return mavka_diia(
//                 "зрізати",
//                 {
//                     "від": mavka_param(0, м_число),
//                     "до": mavka_param(1, [м_число, null])
//                 },
//                 function (args, di, {arg}) {
//                     return a.slice(arg("від"), arg("до") ?? undefined);
//                 }
//             );
//         }
//         return null;
//     }
// }
//
// function mavka_commonGet_list(a, b, di) {
//     if (b.__m_type__ === "number") {
//         return a[b];
//     } else {
//         if (b === "довжина") {
//             return a.length;
//         }
//         if (b === "додати") {
//             return mavka_diia(
//                 "додати",
//                 {
//                     "значення": mavka_param(0, "значення")
//                 },
//                 function (args, di, {arg}) {
//                     a.push(arg("значення"));
//                     return a;
//                 }
//             );
//         }
//         if (b === "забрати") {
//             return mavka_diia(
//                 "забрати",
//                 {},
//                 function () {
//                     return a.pop();
//                 }
//             );
//         }
//         if (b === "отримати") {
//             return mavka_diia(
//                 "отримати",
//                 {
//                     "позиція": mavka_param(0, м_число)
//                 },
//                 function (args, di, {arg}) {
//                     return a[arg("позиція")];
//                 }
//             );
//         }
//         if (b === "сортувати") {
//             return mavka_diia(
//                 "сортувати",
//                 {
//                     "дія_порівняння": mavka_param(0, м_Дія)
//                 },
//                 function (args, di, {arg}) {
//                     return a.sort((a, b) => mavka_call(arg("дія_порівняння"), [a, b], di));
//                 }
//             );
//         }
//         if (b === "фільтрувати") {
//             return mavka_diia(
//                 "фільтрувати",
//                 {
//                     "дія_перевірки": mavka_param(0, м_Дія)
//                 },
//                 function (args, di, {arg}) {
//                     return a.filter((v) => mavka_call(arg("дія_перевірки"), [v], di));
//                 }
//             );
//         }
//         if (b === "знайти") {
//             return mavka_diia(
//                 "знайти",
//                 {
//                     "дія_перевірки": mavka_param(0, м_Дія)
//                 },
//                 function (args, di, {arg}) {
//                     return a.find((v) => mavka_call(arg("дія_перевірки"), [v], di));
//                 }
//             );
//         }
//         if (b === "знайти_позицію") {
//             return mavka_diia(
//                 "знайти_позицію",
//                 {
//                     "дія_перевірки": mavka_param(0, м_Дія)
//                 },
//                 function (args, di, {arg}) {
//                     return a.findIndex((v) => mavka_call(arg("дія_перевірки"), [v], di));
//                 }
//             );
//         }
//         if (b === "перетворити") {
//             return mavka_diia(
//                 "перетворити",
//                 {
//                     "дія_перетворення": mavka_param(0, м_Дія)
//                 },
//                 function (args, di, {arg}) {
//                     return a.map((v) => mavka_call(arg("дія_перетворення"), [v], di));
//                 }
//             );
//         }
//         if (b === "заповнити") {
//             return mavka_diia(
//                 "заповнити",
//                 {
//                     "значення": mavka_param(0, "значення")
//                 },
//                 function (args, di, {arg}) {
//                     return a.fill(arg("значення"));
//                 }
//             );
//         }
//         if (b === "злити") {
//             return mavka_diia(
//                 "злити",
//                 {
//                     "значення": mavka_param(0, м_список)
//                 },
//                 function (args, di, {arg}) {
//                     return a.concat(arg("значення"));
//                 }
//             );
//         }
//         if (b === "зʼєднати") {
//             return mavka_diia(
//                 "зʼєднати",
//                 {
//                     "роздільник": mavka_param(0, м_текст, "")
//                 },
//                 function (args, di, {arg}) {
//                     return a.map((v) => mavka_to_string(v, di)).join(arg("роздільник"));
//                 }
//             );
//         }
//         if (b === "обернути") {
//             return mavka_diia(
//                 "обернути",
//                 {},
//                 function () {
//                     return a.reverse();
//                 }
//             );
//         }
//         if (b === "зрізати") {
//             return mavka_diia(
//                 "зрізати",
//                 {
//                     "від": mavka_param(0, м_число),
//                     "до": mavka_param(1, [м_число, null])
//                 },
//                 function (args, di, {arg}) {
//                     return a.slice(arg("від"), arg("до") ?? undefined);
//                 }
//             );
//         }
//         if (b === "скоротити") {
//             return mavka_diia(
//                 "скоротити",
//                 {
//                     "дія_скорочення": mavka_param(0, м_Дія),
//                     "початкове_значення": mavka_param(1)
//                 },
//                 function (args, di, {arg}) {
//                     return a.reduce((acc, v) => mavka_call(arg("дія_скорочення"), [acc, v], di), arg("початкове_значення"));
//                 }
//             );
//         }
//         return null;
//     }
// }
//
// function mavka_commonGet_text(a, b, di) {
//     if (b.__m_type__ === "number") {
//         return a[b];
//     }
//     if (b === "символ") {
//         return mavka_diia(
//             "символ",
//             {
//                 "позиція": mavka_param(0, м_число)
//             },
//             function (args, di, {arg}) {
//                 return a.charAt(arg("позиція"));
//             }
//         );
//     }
//     if (b === "код_символу") {
//         return mavka_diia(
//             "код_символу",
//             {
//                 "позиція": mavka_param(0, м_число)
//             },
//             function (args, di, {arg}) {
//                 return a.charCodeAt(arg("позиція"));
//             }
//         );
//     }
//     if (b === "позиція") {
//         return mavka_diia(
//             "позиція",
//             {
//                 "значення": mavka_param(0, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.indexOf(arg("значення"));
//             }
//         );
//     }
//     if (b === "повторити") {
//         return mavka_diia(
//             "повторити",
//             {
//                 "кількість": mavka_param(0, м_число)
//             },
//             function (args, di, {arg}) {
//                 return a.repeat(arg("кількість"));
//             }
//         );
//     }
//     if (b === "замінити") {
//         return mavka_diia(
//             "замінити",
//             {
//                 "старе_значення": mavka_param(0, м_текст),
//                 "нове_значення": mavka_param(1, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.replaceAll(arg("старе_значення"), arg("нове_значення"));
//             }
//         );
//     }
//     if (b === "замінити_перше") {
//         return mavka_diia(
//             "замінити_перше",
//             {
//                 "старе_значення": mavka_param(0, м_текст),
//                 "нове_значення": mavka_param(1, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.replace(arg("старе_значення"), arg("нове_значення"));
//             }
//         );
//     }
//     if (b === "зрізати") {
//         return mavka_diia(
//             "зрізати",
//             {
//                 "від": mavka_param(0, м_число),
//                 "до": mavka_param(1, [м_число, null])
//             },
//             function (args, di, {arg}) {
//                 return a.substring(arg("від"), arg("до") ?? undefined);
//             }
//         );
//     }
//     if (b === "приєднати") {
//         return mavka_diia(
//             "приєднати",
//             {},
//             function (args, di, {arg}) {
//                 var value = (Array.isArray(p) ? p : Object.values(p))
//                     .map((v) => mavka_to_string(v, di))
//                     .join("");
//                 return a.concat(value);
//             }
//         );
//     }
//     if (b === "розділити") {
//         return mavka_diia(
//             "розділити",
//             {
//                 "роздільник": mavka_param(0, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.split(arg("роздільник"));
//             }
//         );
//     }
//     if (b === "починається_з") {
//         return mavka_diia(
//             "починається_з",
//             {
//                 "значення": mavka_param(0, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.startsWith(arg("значення"));
//             }
//         );
//     }
//     if (b === "закінчується_на") {
//         return mavka_diia(
//             "закінчується_на",
//             {
//                 "значення": mavka_param(0, м_текст)
//             },
//             function (args, di, {arg}) {
//                 return a.endsWith(arg("значення"));
//             }
//         );
//     }
//     if (b === "обрізати") {
//         return mavka_diia(
//             "обрізати",
//             {},
//             function () {
//                 return a.trim();
//             }
//         );
//     }
//     if (b === "обтяти") {
//         return mavka_diia(
//             "обтяти",
//             {},
//             function () {
//                 var lineNumberWhereSmallestIndentationIs = 0;
//                 var lines = a.split("\n");
//                 var smallestIndentation = Infinity;
//                 for (let i = 0; i < lines.length; i++) {
//                     const line = lines[i];
//                     if (!line.trim()) {
//                         continue;
//                     }
//                     const indentation = line.match(/^\s*/)[0].length;
//                     if (indentation < smallestIndentation) {
//                         smallestIndentation = indentation;
//                         lineNumberWhereSmallestIndentationIs = i;
//                     }
//                 }
//                 const result = [];
//                 for (let i = 0; i < lines.length; i++) {
//                     const line = lines[i];
//                     if (!line.trim()) {
//                         continue;
//                     }
//                     result.push(line.slice(smallestIndentation));
//                 }
//                 return result.join("\n");
//             }
//         );
//     }
//     if (b === "довжина") {
//         return a.length;
//     }
//     return null;
// }
//
// function mavka_commonGet(a, b, di, magicDiia) {
//     if (a == null) {
//         throw new MavkaError("Неможливо отримати властивість з \"пусто\".", di);
//     }
//     if (b == null) {
//         return null;
//     }
//     if (a.__m_type__ === "list") {
//         return mavka_commonGet_list(a, b, di);
//     }
//     if (a.__m_type__ === "bytes") {
//         return mavka_commonGet_bytes(a, b, di);
//     }
//     if (a.__m_type__ === "dictionary") {
//         return a.get(b);
//     }
//     if (a.__m_type__ === "text") {
//         return mavka_commonGet_text(a, b, di);
//     }
//     if (!a.__m_props__) {
//         throw new MavkaError(`Неможливо отримати властивість ${mavka_to_pretty_string(b, false)}.`, di);
//     }
//     if (magicDiia) {
//         if (a.__m_props__[magicDiia]) {
//             return a.__m_props__[magicDiia]([b], di);
//         }
//     }
//     return a.__m_props__[b];
// }
//
// function mavka_get(a, b, di) {
//     return mavka_commonGet(a, b, di);
// }
//
// function mavka_getSpecial(a, b, di) {
//     return mavka_commonGet(a, b, di, "чародія_отримати_спеціальну_властивість");
// }
//
// function mavka_commonSet(a, b, c, di, magicDiia) {
//     if (a == null) {
//         throw new MavkaError("Неможливо встановити властивість для \"пусто\".", di);
//     }
//     if (a.__m_type__ === "list" && b.__m_type__ === "number") {
//         a[b] = c;
//         return a;
//     } else if (a.__m_type__ === "bytes" && b.__m_type__ === "number") {
//         a[b] = c;
//         return a;
//     } else if (a.__m_type__ === "dictionary") {
//         a.set(b, c);
//         return a;
//     } else if (a.__m_type__ === "object") {
//         if (magicDiia) {
//             if (a.__m_props__[magicDiia]) {
//                 a.__m_props__[magicDiia]([b, c], di);
//                 return a;
//             }
//         }
//         a.__m_props__[b] = c;
//         return a;
//     } else {
//         throw new MavkaError("Неможливо встановити властивість.", di);
//     }
// }
//
// function mavka_set(a, b, c, di) {
//     return mavka_commonSet(a, b, c, di);
// }
//
// function mavka_setSpecial(a, b, c, di) {
//     return mavka_commonSet(a, b, c, di, "чародія_змінити_спеціальну_властивість");
// }
//
// var mavka_module = (name) => {
//     var value = Object.create(null);
//     value.__m_structure__ = м_Модуль;
//     value.__m_type__ = "module";
//     value.__m_props__ = Object.create(null);
//     value.__m_name__ = name;
//     return value;
// };
//
// function mavka_structure(name, parent = null, params = {}, di = null) {
//     var mergedParams = params;
//     var mergedMethods = Object.create(null);
//     if (parent && parent.__m_type__ !== "structure") {
//         throw new MavkaError("Неможливо створити структуру.", di);
//     }
//     // todo: check for circular inheritance
//     // todo: check for duplicate params and methods
//     var currStructure = parent;
//     while (currStructure != null && currStructure.__m_type__ === "structure") {
//         for (const [k, v] of Object.entries(currStructure.__m_params__)) {
//             if (mergedParams[k]) {
//                 continue;
//             }
//             mergedParams[k] = v;
//         }
//         for (const [k, v] of Object.entries(currStructure.__m_methods__)) {
//             if (mergedMethods[k]) {
//                 continue;
//             }
//             mergedMethods[k] = v;
//         }
//         currStructure = currStructure.__m_parent__;
//     }
//     var structure = class {
//         static __m_type__ = "structure";
//         static __m_props__ = Object.create(null);
//         static __m_name__ = name;
//         // structure specific
//         static __m_params__ = mergedParams;
//         static __m_methods__ = mergedMethods;
//         static __m_parent__ = parent;
//
//         constructor() {
//             this.__m_structure__ = structure;
//             this.__m_type__ = "object";
//             this.__m_props__ = Object.create(null);
//             // fill props and attach methods
//             for (const [k, v] of Object.entries(structure.__m_params__)) {
//                 if (this.__m_props__[k]) {
//                     continue;
//                 }
//                 this.__m_props__[k] = v.defaultValue ?? null;
//             }
//             for (const [methodName, method] of Object.entries(structure.__m_methods__)) {
//                 if (this.__m_props__[methodName]) {
//                     continue;
//                 }
//                 this.__m_props__[methodName] = mavka_diia(methodName, method.__m_params__, (args, callDi) => {
//                     return method(this, args, callDi);
//                 }, undefined, di);
//             }
//         }
//
//         toJSON() {
//             const result = Object.create(null);
//             for (const [k, v] of Object.entries(structure.__m_params__)) {
//                 result[k] = this.__m_props__[k];
//             }
//             return result;
//         }
//     };
//     structure.__m_props__["чародія_викликати"] = mavka_diia("чародія_викликати", {}, (args, callDi) => {
//         var value = new structure();
//         if (value.__m_props__["чародія_створити"]) {
//             value.__m_props__["чародія_створити"].__m_call__(args, callDi);
//         } else {
//             for (const [k, v] of Object.entries(structure.__m_params__)) {
//                 value.__m_props__[k] = mavka_arg(
//                     args,
//                     v.get("позиція"),
//                     k,
//                     v.get("тип"),
//                     v.get("значення"),
//                     callDi
//                 );
//             }
//         }
//         if (value.__m_props__["чародія_після_створення"]) {
//             value.__m_props__["чародія_після_створення"].__m_call__(args, callDi);
//         }
//         return value;
//     }, undefined, di);
//     return structure;
// }