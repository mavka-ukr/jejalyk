# Джеджалик

Компілятор Мавки для Вебу.

## Встановлення

```shell
npm i jejalyk
```

## Використання

```javascript
import jejalyk from "jejalyk";
import fs from "fs";

const wasm = fs.readFileSync("./node_modules/jejalyk/jejalyk.wasm");

const result = await jejalyk.compile(
    `друк("Привіт!")`,
    {
        wasm,
        // todo: module loading functions
    }
);

console.log(result);
```