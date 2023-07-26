NPM CHECKLIST
=============

| Action                                                             | Target  | Done  | Description |
| ------------------------------------------------------------------ | ------- | ----- | ----------- |
| Run `npm init --scope="[organization]"`                            | shell   | -     | ...         |
| Add `"type"="module",` in `package.json`                           | editor  | -     | ...         |
| Create `./src/index.js`                                            | editor  | -     | ...         |
| Install `mocha` (`npm install --save-dev mocha`)                   | shell   | -     | ...         |
| Add `package-lock.json` in `.gitignore`                            | editor  | -     | ...         |
| Create `./test/index.js`                                           | editor  | -     | ...         |
| Test `npm run test`                                                | editor  | -     | ...         |
| Add javascript & nodejs badge in README.md                         | editor  | -     | ...         |
| Publish `npm publish --access public`                              | shell   | -     | ...         |
| Check npmjs.org                                                    | browser | -     | ...         |
| Check jsdelivr https://cdn.jsdelivr.net/npm/[organization/package] | browser | -     | ...         |

### CREATE FIRST TEST FILE

__./test/index.js__

```js
describe("[name]", () => {
    it("[iteration]", async () => {
        console.log("hello world");
    });
});
```

### ADD JAVASCRIPT & NODEJS BADGE IN README.md

```
![Node js](https://img.shields.io/badge/Node.js-339933?style=flat-square&logo=Node.js&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black)
```