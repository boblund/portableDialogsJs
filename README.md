# Portable Dialogs for NodeJS

Portable Dialogs for NodeJS (pdjs) is a NodeJS wrapper for [portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs) that provides file, message and notify dialogs for Windows, MacOS and Linux.

The motivation for pdjs was to add these dialogs to NodeJS applications that use webview for the user interface, as webviews don't typically provide these types of dialogs.

[Concepts](#concepts)

[Using](#using)

[License](#license)

# Concepts <a name="concepts"></a>

[portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs) is a single include file without dependencies written in C++. pdjs uses a ```node-api-addon``` to expose ```save_file```, ```open_file```, ```message``` and ```notfiy``` to NodeJS applications. Note that the ```select_folder``` dialog is not exposed as there doesn't seem to be a use case. It would be easy for a developer to add exposing this dialog.

# Using <a name="using"></a>

Install ```node-gyp``` if not installed:

```
npm install node-gyp -g
```

Install pdjs:

```
git clone https://github.com/boblund/pdjs
cd pdjs
npm install
```

Run the test:

```
npm test
```

Build an excutable version of the test using [pkg](https://www.npmjs.com/package/pkg):

```
pkg .
```

This will build an executable file in ```./dist``` for Mac arm64. Other targets can be built by changing the target property of pkg in ```package.json```.

# License <a name="license"></a>

Creative Commons Attribution-NonCommercial 4.0 International
