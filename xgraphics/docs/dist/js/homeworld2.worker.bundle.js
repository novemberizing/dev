/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/js/homeworld2.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/js/homeworld2.js":
/*!******************************!*\
  !*** ./src/js/homeworld2.js ***!
  \******************************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _homeworld2_singlemesh_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./homeworld2/singlemesh.js */ "./src/js/homeworld2/singlemesh.js");



/***/ }),

/***/ "./src/js/homeworld2/singlemesh.js":
/*!*****************************************!*\
  !*** ./src/js/homeworld2/singlemesh.js ***!
  \*****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Singlemesh; });
/* harmony import */ var _x_graphics_complex_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/complex.js */ "./src/js/x/graphics/complex.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }




var Singlemesh = /*#__PURE__*/function (_Complex) {
  _inherits(Singlemesh, _Complex);

  function Singlemesh(level, status) {
    _classCallCheck(this, Singlemesh);

    return _possibleConstructorReturn(this, _getPrototypeOf(Singlemesh).call(this, "", level, status));
  }

  _createClass(Singlemesh, [{
    key: "level",
    get: function get() {
      return this.__level;
    }
  }, {
    key: "status",
    set: function set(v) {
      this.__status = v;

      this.__children.forEach(function (o) {
        return o.status = v;
      });
    }
  }]);

  return Singlemesh;
}(_x_graphics_complex_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/complex.js":
/*!**************************************!*\
  !*** ./src/js/x/graphics/complex.js ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Complex; });
/* harmony import */ var _obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./obj.js */ "./src/js/x/graphics/obj.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }



var Complex = /*#__PURE__*/function (_Obj) {
  _inherits(Complex, _Obj);

  function Complex(name, level) {
    var _this;

    _classCallCheck(this, Complex);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(Complex).call(this, name, level));
    _this.__children = new Array();
    return _this;
  }

  _createClass(Complex, [{
    key: "add",
    value: function add(o) {
      this.__children.push(o);
    }
  }, {
    key: "render",
    value: function render(application, model, level) {
      var gl = application.gl;

      this.__children.forEach(function (o) {
        o.render(application, model, level);
      });
    }
  }, {
    key: "load",
    value: function load(application) {
      this.__children.forEach(function (o) {
        o.load(application);
      });

      this.__load = true;
    }
  }, {
    key: "unload",
    value: function unload(application) {
      this.__children.forEach(function (o) {
        o.unload(application);
      });

      this.__load = false;
    }
  }]);

  return Complex;
}(_obj_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/matrix.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/matrix.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Matrix; });
/* harmony import */ var _vector_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./vector.js */ "./src/js/x/graphics/vector.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Matrix = /*#__PURE__*/function () {
  function Matrix() {
    _classCallCheck(this, Matrix);
  }

  _createClass(Matrix, null, [{
    key: "identity",
    value: function identity() {
      return [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
    }
  }, {
    key: "zero",
    value: function zero() {
      return [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    }
  }, {
    key: "deepcopy",
    value: function deepcopy(m) {
      var result = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

      for (var i = 0; i < result.length; i++) {
        result[i] = m[i];
      }

      return result;
    }
  }, {
    key: "lookat",
    value: function lookat(eye, center, up) {
      var f = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].normalize(_vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].minus(center, eye));
      var s = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].normalize(_vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].cross(f, up));
      var u = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].cross(s, f);
      var result = Matrix.identity();
      result[0 * 4 + 0] = s[0];
      result[1 * 4 + 0] = s[1];
      result[2 * 4 + 0] = s[2];
      result[0 * 4 + 1] = u[0];
      result[1 * 4 + 1] = u[1];
      result[2 * 4 + 1] = u[2];
      result[0 * 4 + 2] = -f[0];
      result[1 * 4 + 2] = -f[1];
      result[2 * 4 + 2] = -f[2];
      result[3 * 4 + 0] = -_vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].dot(s, eye);
      result[3 * 4 + 1] = -_vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].dot(u, eye);
      result[3 * 4 + 2] = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].dot(f, eye);
      return result;
    }
  }, {
    key: "perspective",
    value: function perspective(fovy, aspect, near, far) {
      var half = Math.tan(fovy / 2.0);
      var result = Matrix.zero();
      result[0] = 1.0 / (aspect * half);
      result[4 + 1] = 1.0 / half;
      result[2 * 4 + 2] = (far + near) / (near - far);
      result[2 * 4 + 3] = -1.0;
      result[3 * 4 + 2] = -(2.0 * far * near) / (far - near);
      return result;
    }
  }, {
    key: "multiply",
    value: function multiply(x, y) {
      var result = Matrix.zero();
      result[0 * 4 + 0] = x[0 * 4 + 0] * y[0 * 4 + 0] + x[0 * 4 + 1] * y[1 * 4 + 0] + x[0 * 4 + 2] * y[2 * 4 + 0] + x[0 * 4 + 3] * y[3 * 4 + 0];
      result[0 * 4 + 1] = x[0 * 4 + 0] * y[0 * 4 + 1] + x[0 * 4 + 1] * y[1 * 4 + 1] + x[0 * 4 + 2] * y[2 * 4 + 1] + x[0 * 4 + 3] * y[3 * 4 + 1];
      result[0 * 4 + 2] = x[0 * 4 + 0] * y[0 * 4 + 2] + x[0 * 4 + 1] * y[1 * 4 + 2] + x[0 * 4 + 2] * y[2 * 4 + 2] + x[0 * 4 + 3] * y[3 * 4 + 2];
      result[0 * 4 + 3] = x[0 * 4 + 0] * y[0 * 4 + 3] + x[0 * 4 + 1] * y[1 * 4 + 3] + x[0 * 4 + 2] * y[2 * 4 + 3] + x[0 * 4 + 3] * y[3 * 4 + 3];
      result[1 * 4 + 0] = x[1 * 4 + 0] * y[0 * 4 + 0] + x[1 * 4 + 1] * y[1 * 4 + 0] + x[1 * 4 + 2] * y[2 * 4 + 0] + x[1 * 4 + 3] * y[3 * 4 + 0];
      result[1 * 4 + 1] = x[1 * 4 + 0] * y[0 * 4 + 1] + x[1 * 4 + 1] * y[1 * 4 + 1] + x[1 * 4 + 2] * y[2 * 4 + 1] + x[1 * 4 + 3] * y[3 * 4 + 1];
      result[1 * 4 + 2] = x[1 * 4 + 0] * y[0 * 4 + 2] + x[1 * 4 + 1] * y[1 * 4 + 2] + x[1 * 4 + 2] * y[2 * 4 + 2] + x[1 * 4 + 3] * y[3 * 4 + 2];
      result[1 * 4 + 3] = x[1 * 4 + 0] * y[0 * 4 + 3] + x[1 * 4 + 1] * y[1 * 4 + 3] + x[1 * 4 + 2] * y[2 * 4 + 3] + x[1 * 4 + 3] * y[3 * 4 + 3];
      result[2 * 4 + 0] = x[2 * 4 + 0] * y[0 * 4 + 0] + x[2 * 4 + 1] * y[1 * 4 + 0] + x[2 * 4 + 2] * y[2 * 4 + 0] + x[2 * 4 + 3] * y[3 * 4 + 0];
      result[2 * 4 + 1] = x[2 * 4 + 0] * y[0 * 4 + 1] + x[2 * 4 + 1] * y[1 * 4 + 1] + x[2 * 4 + 2] * y[2 * 4 + 1] + x[2 * 4 + 3] * y[3 * 4 + 1];
      result[2 * 4 + 2] = x[2 * 4 + 0] * y[0 * 4 + 2] + x[2 * 4 + 1] * y[1 * 4 + 2] + x[2 * 4 + 2] * y[2 * 4 + 2] + x[2 * 4 + 3] * y[3 * 4 + 2];
      result[2 * 4 + 3] = x[2 * 4 + 0] * y[0 * 4 + 3] + x[2 * 4 + 1] * y[1 * 4 + 3] + x[2 * 4 + 2] * y[2 * 4 + 3] + x[2 * 4 + 3] * y[3 * 4 + 3];
      result[3 * 4 + 0] = x[3 * 4 + 0] * y[0 * 4 + 0] + x[3 * 4 + 1] * y[1 * 4 + 0] + x[3 * 4 + 2] * y[2 * 4 + 0] + x[3 * 4 + 3] * y[3 * 4 + 0];
      result[3 * 4 + 1] = x[3 * 4 + 0] * y[0 * 4 + 1] + x[3 * 4 + 1] * y[1 * 4 + 1] + x[3 * 4 + 2] * y[2 * 4 + 1] + x[3 * 4 + 3] * y[3 * 4 + 1];
      result[3 * 4 + 2] = x[3 * 4 + 0] * y[0 * 4 + 2] + x[3 * 4 + 1] * y[1 * 4 + 2] + x[3 * 4 + 2] * y[2 * 4 + 2] + x[3 * 4 + 3] * y[3 * 4 + 2];
      result[3 * 4 + 3] = x[3 * 4 + 0] * y[0 * 4 + 3] + x[3 * 4 + 1] * y[1 * 4 + 3] + x[3 * 4 + 2] * y[2 * 4 + 3] + x[3 * 4 + 3] * y[3 * 4 + 3];
      return result;
    }
  }, {
    key: "translate",
    value: function translate(m, v) {
      var result = Matrix.deepcopy(m);
      result[3 * 4 + 0] = m[0 * 4 + 0] * v[0] + m[1 * 4 + 0] * v[1] + m[2 * 4 + 0] * v[2] + m[3 * 4 + 0];
      result[3 * 4 + 1] = m[0 * 4 + 1] * v[0] + m[1 * 4 + 1] * v[1] + m[2 * 4 + 1] * v[2] + m[3 * 4 + 1];
      result[3 * 4 + 2] = m[0 * 4 + 2] * v[0] + m[1 * 4 + 2] * v[1] + m[2 * 4 + 2] * v[2] + m[3 * 4 + 2];
      result[3 * 4 + 3] = m[0 * 4 + 3] * v[0] + m[1 * 4 + 3] * v[1] + m[2 * 4 + 3] * v[2] + m[3 * 4 + 3];
      return result;
    }
  }, {
    key: "rotate",
    value: function rotate(m, angle, v) {
      var c = Math.cos(angle);
      var s = Math.sin(angle);
      var axis = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].normalize(v);
      var temp = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].multiply(axis, 1 - c);
      var rotation = Matrix.zero();
      rotation[0 * 4 + 0] = c + temp[0] * axis[0];
      rotation[0 * 4 + 1] = temp[0] * axis[1] + s * axis[2];
      rotation[0 * 4 + 2] = temp[0] * axis[2] - s * axis[1];
      rotation[1 * 4 + 0] = temp[1] * axis[0] - s * axis[2];
      rotation[1 * 4 + 1] = c + temp[1] * axis[1];
      rotation[1 * 4 + 2] = temp[1] * axis[2] + s * axis[0];
      rotation[2 * 4 + 0] = temp[2] * axis[0] + s * axis[1];
      rotation[2 * 4 + 1] = temp[2] * axis[1] - s * axis[0];
      rotation[2 * 4 + 2] = c + temp[2] * axis[2];
      var result = Matrix.zero();
      result[0 * 4 + 0] = m[0 * 4 + 0] * rotation[0 * 4 + 0] + m[1 * 4 + 0] * rotation[0 * 4 + 1] + m[2 * 4 + 0] * rotation[0 * 4 + 2];
      result[0 * 4 + 1] = m[0 * 4 + 1] * rotation[0 * 4 + 0] + m[1 * 4 + 1] * rotation[0 * 4 + 1] + m[2 * 4 + 1] * rotation[0 * 4 + 2];
      result[0 * 4 + 2] = m[0 * 4 + 2] * rotation[0 * 4 + 0] + m[1 * 4 + 2] * rotation[0 * 4 + 1] + m[2 * 4 + 2] * rotation[0 * 4 + 2];
      result[0 * 4 + 3] = m[0 * 4 + 3] * rotation[0 * 4 + 0] + m[1 * 4 + 3] * rotation[0 * 4 + 1] + m[2 * 4 + 3] * rotation[0 * 4 + 2];
      result[1 * 4 + 0] = m[0 * 4 + 0] * rotation[1 * 4 + 0] + m[1 * 4 + 0] * rotation[1 * 4 + 1] + m[2 * 4 + 0] * rotation[1 * 4 + 2];
      result[1 * 4 + 1] = m[0 * 4 + 1] * rotation[1 * 4 + 0] + m[1 * 4 + 1] * rotation[1 * 4 + 1] + m[2 * 4 + 1] * rotation[1 * 4 + 2];
      result[1 * 4 + 2] = m[0 * 4 + 2] * rotation[1 * 4 + 0] + m[1 * 4 + 2] * rotation[1 * 4 + 1] + m[2 * 4 + 2] * rotation[1 * 4 + 2];
      result[1 * 4 + 3] = m[0 * 4 + 3] * rotation[1 * 4 + 0] + m[1 * 4 + 3] * rotation[1 * 4 + 1] + m[2 * 4 + 3] * rotation[1 * 4 + 2];
      result[2 * 4 + 0] = m[0 * 4 + 0] * rotation[2 * 4 + 0] + m[1 * 4 + 0] * rotation[2 * 4 + 1] + m[2 * 4 + 0] * rotation[2 * 4 + 2];
      result[2 * 4 + 1] = m[0 * 4 + 1] * rotation[2 * 4 + 0] + m[1 * 4 + 1] * rotation[2 * 4 + 1] + m[2 * 4 + 1] * rotation[2 * 4 + 2];
      result[2 * 4 + 2] = m[0 * 4 + 2] * rotation[2 * 4 + 0] + m[1 * 4 + 2] * rotation[2 * 4 + 1] + m[2 * 4 + 2] * rotation[2 * 4 + 2];
      result[2 * 4 + 3] = m[0 * 4 + 3] * rotation[2 * 4 + 0] + m[1 * 4 + 3] * rotation[2 * 4 + 1] + m[2 * 4 + 3] * rotation[2 * 4 + 2];
      result[3 * 4 + 0] = m[3 * 4 + 0];
      result[3 * 4 + 1] = m[3 * 4 + 1];
      result[3 * 4 + 2] = m[3 * 4 + 2];
      result[3 * 4 + 3] = m[3 * 4 + 3];
      return result;
    }
  }, {
    key: "scale",
    value: function scale(m, v) {
      var result = Matrix.zero();
      result[0 * 4 + 0] = m[0 * 4 + 0] * v[0];
      result[0 * 4 + 1] = m[0 * 4 + 1] * v[0];
      result[0 * 4 + 2] = m[0 * 4 + 2] * v[0];
      result[0 * 4 + 3] = m[0 * 4 + 3] * v[0];
      result[1 * 4 + 0] = m[1 * 4 + 0] * v[1];
      result[1 * 4 + 1] = m[1 * 4 + 1] * v[1];
      result[1 * 4 + 2] = m[1 * 4 + 2] * v[1];
      result[1 * 4 + 3] = m[1 * 4 + 3] * v[1];
      result[2 * 4 + 0] = m[2 * 4 + 0] * v[2];
      result[2 * 4 + 1] = m[2 * 4 + 1] * v[2];
      result[2 * 4 + 2] = m[2 * 4 + 2] * v[2];
      result[2 * 4 + 3] = m[2 * 4 + 3] * v[2];
      result[3 * 4 + 0] = m[3 * 4 + 0];
      result[3 * 4 + 1] = m[3 * 4 + 1];
      result[3 * 4 + 2] = m[3 * 4 + 2];
      result[3 * 4 + 3] = m[3 * 4 + 3];
      return result;
    }
  }, {
    key: "vectorMultiply",
    value: function vectorMultiply(m, v) {
      var result = [0, 0, 0, 0];
      result[0] = m[0 * 4 + 0] * v[0] + m[0 * 4 + 1] * v[1] + m[0 * 4 + 2] * v[2] + m[0 * 4 + 3] * v[3];
      result[1] = m[1 * 4 + 0] * v[0] + m[1 * 4 + 1] * v[1] + m[1 * 4 + 2] * v[2] + m[1 * 4 + 3] * v[3];
      result[2] = m[2 * 4 + 0] * v[0] + m[2 * 4 + 1] * v[1] + m[2 * 4 + 2] * v[2] + m[2 * 4 + 3] * v[3];
      result[3] = m[3 * 4 + 0] * v[0] + m[3 * 4 + 1] * v[1] + m[3 * 4 + 2] * v[2] + m[3 * 4 + 3] * v[3];
      return result;
    }
  }]);

  return Matrix;
}();



/***/ }),

/***/ "./src/js/x/graphics/obj.js":
/*!**********************************!*\
  !*** ./src/js/x/graphics/obj.js ***!
  \**********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Obj; });
/* harmony import */ var _reference_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./reference.js */ "./src/js/x/graphics/reference.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Obj = /*#__PURE__*/function () {
  function Obj(name, level) {
    _classCallCheck(this, Obj);

    this.__name = name;
    this.__level = level || 0;
    this.__load = false;
  }

  _createClass(Obj, [{
    key: "render",
    value: function render(gl, model, level) {
      console.log("render");
    }
  }, {
    key: "load",
    value: function load(gl) {
      this.__load = true;
    }
  }, {
    key: "unload",
    value: function unload(gl) {
      this.__load = false;
    }
  }, {
    key: "build",
    value: function build(name) {
      return new _reference_js__WEBPACK_IMPORTED_MODULE_0__["default"](name, this);
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "status",
    set: function set(v) {
      this.__status = v;
    }
  }]);

  return Obj;
}();



/***/ }),

/***/ "./src/js/x/graphics/reference.js":
/*!****************************************!*\
  !*** ./src/js/x/graphics/reference.js ***!
  \****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Reference; });
/* harmony import */ var _vector_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./vector.js */ "./src/js/x/graphics/vector.js");
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./matrix.js */ "./src/js/x/graphics/matrix.js");



class Reference
{
    constructor(name, object, location, rotation, scale, axis)
    {
        this.__name = name;
        this.__location = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(location, 0.0);
        this.__rotation = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(rotation, 0.0);
        this.__scale = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(scale || [1, 1, 1, 0], 0.0);
        this.__axis = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(axis, 0.0);
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].identity();
        this.__level = 0;
        this.__objects = new Map();
        this.__children = new Map();

        if(object)
        {
            this.__objects.set(object.name, object);
        }
    }

    render(application, model, level)
    {
        const gl = application.gl;

        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].translate(model, this.__location);
        if(this.__axis[0] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[0], [1, 0, 0, 0]);
        }
        if(this.__axis[1] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[1], [0, 1, 0, 0]);
        }
        if(this.__axis[2] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[2], [0, 0, 1, 0]);
        }

        if(this.__rotation[0] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[0], [1, 0, 0, 0]);
        }
        if(this.__rotation[1] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[1], [0, 1, 0, 0]);
        }
        if(this.__rotation[2] !== 0)
        {
            this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[2], [0, 0, 1, 0]);
        }

        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].scale(this.__model, this.__scale);

        this.__objects.forEach((object, name) => {
            // console.log(object);
            object.render(application, this.__model, level);
        });

        this.__children.forEach((reference, name) => {
            reference.render(application, this.__model, level);
        });
    }

    get name(){ return this.__name; }
    get objects(){ return this.__objects; }
    get children(){ return this.__children; }
}


/***/ }),

/***/ "./src/js/x/graphics/vector.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/vector.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Vector; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var __degree = 57.295779513082320876798154814105;
var __radian = 0.01745329251994329576923690768489;

var Vector = /*#__PURE__*/function () {
  function Vector() {
    _classCallCheck(this, Vector);
  }

  _createClass(Vector, null, [{
    key: "four",
    value: function four(o, end) {
      o = o || [];

      if (o.length < 4) {
        while (o.length < 3) {
          o.push(0);
        }

        o.push(end || 0);
        return o;
      } else {
        return o.splice(0, 4);
      }
    }
  }, {
    key: "two",
    value: function two(o) {
      o = o || [];

      if (o.length < 2) {
        while (o.length < 2) {
          o.push(0);
        }

        return o;
      } else {
        return o.splice(0, 2);
      }
    }
  }, {
    key: "degree",
    value: function degree(o) {
      var result = [0, 0, 0, 0];
      result[0] = o[0] * __degree;
      result[1] = o[1] * __degree;
      result[2] = o[2] * __degree;
      result[3] = o[3] * __degree;
      return result;
    }
  }, {
    key: "radian",
    value: function radian(o) {
      var result = [0, 0, 0, 0];
      result[0] = o[0] * __radian;
      result[1] = o[1] * __radian;
      result[2] = o[2] * __radian;
      result[3] = o[3] * __radian;
      return result;
    }
  }, {
    key: "dot",
    value: function dot(x, y) {
      var result = 0;

      for (var i = 0; i < 4; i++) {
        result += x[i] * y[i];
      }

      return result;
    }
  }, {
    key: "normalize",
    value: function normalize(o) {
      var dot = Math.sqrt(Vector.dot(o, o));
      var result = [0, 0, 0, 0];

      for (var i = 0; i < 4; i++) {
        result[i] = o[i] / dot;
      }

      return result;
    }
  }, {
    key: "cross",
    value: function cross(x, y) {
      var result = [0, 0, 0, 0];
      result[0] = x[1] * y[2] - x[2] * y[1];
      result[1] = x[2] * y[0] - x[0] * y[2];
      result[2] = x[0] * y[1] - x[1] * y[0];
      return result;
    }
  }, {
    key: "minus",
    value: function minus(x, y) {
      var result = [0, 0, 0, 0];

      for (var i = 0; i < 4; i++) {
        result[i] = x[i] - y[i];
      }

      return result;
    }
  }, {
    key: "plus",
    value: function plus(x, y) {
      var result = [0, 0, 0, 0];

      for (var i = 0; i < 4; i++) {
        result[i] = x[i] + y[i];
      }

      return result;
    }
  }, {
    key: "multiply",
    value: function multiply(v, c) {
      var result = [0, 0, 0, 0];

      for (var i = 0; i < 4; i++) {
        result[i] = v[i] * c;
      }

      return result;
    }
  }]);

  return Vector;
}();



/***/ })

/******/ });
//# sourceMappingURL=homeworld2.worker.bundle.js.map