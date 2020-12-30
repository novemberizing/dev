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
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/js/x.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/js/homeworld2/goblinmesh.js":
/*!*****************************************!*\
  !*** ./src/js/homeworld2/goblinmesh.js ***!
  \*****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Goblinmesh; });
/* harmony import */ var _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/obj.js */ "./src/js/x/graphics/obj.js");


class Goblinmesh extends _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(name, parent, status)
    {
        super(name, 0, status);

        this.__singlemesh = null;
        this.__parent = parent;
    }

    get singlemesh(){ return this.__singlemesh; }
    get status(){ return this.__status; }
    get name(){ return this.__name; }
    get parent(){ return this.__parent; }

    set singlemesh(o){ this.__singlemesh = o; }

    set status(v)
    {
        this.__status = v;
        this.__singlemesh.status = v;
    }

    render(application, model, level)
    {
        this.__singlemesh.render(application, model, level);

    }

    load(application)
    {
        this.__singlemesh.load(application);
        this.__load = true;
    }


    unload(application)
    {
        this.__singlemesh.unload(application);
        this.__load = false;
    }
}


/***/ }),

/***/ "./src/js/homeworld2/joint.js":
/*!************************************!*\
  !*** ./src/js/homeworld2/joint.js ***!
  \************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Joint; });
/* harmony import */ var _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/matrix.js */ "./src/js/x/graphics/matrix.js");
/* harmony import */ var _reference_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./reference.js */ "./src/js/homeworld2/reference.js");



class Joint
{
    constructor(name, parent, location, rotation, scale, axis, freedom)
    {
        this.__name = name;
        this.__parent = parent;
        this.__location = location;
        this.__rotation = rotation;
        this.__scale = scale;
        this.__axis = axis;
        this.__freedom = freedom;
        this.__children = new Map();
        this.__objects = new Array();
        this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_0__["default"].identity();
    }

    get name(){ return this.__name; }
    get parent(){ return this.__parent; }
    get children(){ return this.__children; }
    get objects(){ return this.__objects; }

    build(name)
    {
        let reference = new _reference_js__WEBPACK_IMPORTED_MODULE_1__["default"](name, this.__location, this.__rotation, this.__scale, this.__axis);
        this.__objects.forEach(o => {
            // console.log(o);
            reference.objects.set(o.name, o);
        });
        this.__children.forEach(o => {
            reference.children.set(o.name, o.build(o.name));
        });
        return reference;
    }
}


/***/ }),

/***/ "./src/js/homeworld2/material.js":
/*!***************************************!*\
  !*** ./src/js/homeworld2/material.js ***!
  \***************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Material; });

class Material
{
    constructor(name, shader, diffuse, glow)
    {
        this.__name = name;
        this.__shader = shader;
        this.__diffuse = diffuse;
        this.__glow = glow;
    }
    
    get shader(){ return this.__shader; }
    get diffuse(){ return this.__diffuse; }
}


/***/ }),

/***/ "./src/js/homeworld2/multimesh.js":
/*!****************************************!*\
  !*** ./src/js/homeworld2/multimesh.js ***!
  \****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Multimesh; });
/* harmony import */ var _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/obj.js */ "./src/js/x/graphics/obj.js");


class Multimesh extends _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(name, parent, status)
    {
        super(name, 0, status);
        this.__parent = parent;
        this.__singlemesh = new Map();
    }

    get singlemesh(){ return this.__singlemesh; }
    get status(){ return this.__status; }
    get name(){ return this.__name; }
    get parent(){ return this.__parent; }

    set status(v)
    {
        this.__status = v;
        this.__singlemesh.forEach(singlemesh => { singlemesh.status = v; });
    }

    render(application, model, level)
    {
        this.__singlemesh.forEach((singlemesh, index) => {
            if(level === index)
            {
                singlemesh.render(application, model, level);
            }
        });
    }

    load(application)
    {
        this.__singlemesh.forEach(singlemesh => {
            singlemesh.load(application);
        });
        this.__load = true;
    }

    unload(application)
    {
        this.__singlemesh.forEach(singlemesh => {
            singlemesh.unload(application);
        });
        this.__load = false;
    }
}


/***/ }),

/***/ "./src/js/homeworld2/obj.js":
/*!**********************************!*\
  !*** ./src/js/homeworld2/obj.js ***!
  \**********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Homeworld2Object; });
/* harmony import */ var _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/obj.js */ "./src/js/x/graphics/obj.js");
/* harmony import */ var _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../x/graphics/matrix.js */ "./src/js/x/graphics/matrix.js");
/* harmony import */ var _reference_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./reference.js */ "./src/js/homeworld2/reference.js");




class Homeworld2Object extends _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(name, level)
    {
        super(name, level);
        this.__version = 0;
        this.__category = "";
        this.__materials = new Array();
        this.__textures = new Array();
        this.__multimesh = new Map();
        this.__goblinmesh = new Map();
        this.__joints = new Map();
        this.__root = null;
    }

    load(application) {
        console.log("homeworld2 object init");
        console.log({version: this.__version, category: this.__category});
        this.__textures.forEach(texture => {
            texture.load(application);
        });
        this.__multimesh.forEach(multimesh => {
            multimesh.load(application);
        });

        this.__goblinmesh.forEach(goblinmesh => {
            goblinmesh.load(application);
        });
        this.__load = true;
    }

    unload(application)
    {
        this.__multimesh.forEach(multimesh => {
            multimesh.unload(application);
        });

        this.__goblinmesh.forEach(goblinmesh => {
            goblinmesh.unload(application);
        });
        this.__textures.forEach(texture => {
            texture.unload(application);
        });
        this.__load = false;
    }

    material(index)
    {
        return this.__materials[index];
    }

    texture(index)
    {
        return this.__textures[index];
    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }
    get multimesh(){ return this.__multimesh; }
    get goblinmesh(){ return this.__goblinmesh; }
    get joints(){ return this.__joints; }
    get textures(){ return this.__textures; }
    get materials(){ return this.__materials; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }
    set root(o){ this.__root = o; }

    build(name)
    {
        console.log("root build");
        return this.__root.build(name);
    }
}


/***/ }),

/***/ "./src/js/homeworld2/object.file.js":
/*!******************************************!*\
  !*** ./src/js/homeworld2/object.file.js ***!
  \******************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return ObjectFile; });
/* harmony import */ var _obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./obj.js */ "./src/js/homeworld2/obj.js");
/* harmony import */ var _multimesh_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./multimesh.js */ "./src/js/homeworld2/multimesh.js");
/* harmony import */ var _goblinmesh_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./goblinmesh.js */ "./src/js/homeworld2/goblinmesh.js");
/* harmony import */ var _singlemesh_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./singlemesh.js */ "./src/js/homeworld2/singlemesh.js");
/* harmony import */ var _primitive_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./primitive.js */ "./src/js/homeworld2/primitive.js");
/* harmony import */ var _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ../x/graphics/obj.js */ "./src/js/x/graphics/obj.js");
/* harmony import */ var _x_graphics_buffer_js__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ../x/graphics/buffer.js */ "./src/js/x/graphics/buffer.js");
/* harmony import */ var _x_graphics_vertices_js__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ../x/graphics/vertices.js */ "./src/js/x/graphics/vertices.js");
/* harmony import */ var _x_core_command_js__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! ../x/core/command.js */ "./src/js/x/core/command.js");
/* harmony import */ var _joint_js__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! ./joint.js */ "./src/js/homeworld2/joint.js");
/* harmony import */ var _x_graphics_texture_js__WEBPACK_IMPORTED_MODULE_10__ = __webpack_require__(/*! ../x/graphics/texture.js */ "./src/js/x/graphics/texture.js");
/* harmony import */ var _x_graphics_mipmap_js__WEBPACK_IMPORTED_MODULE_11__ = __webpack_require__(/*! ../x/graphics/mipmap.js */ "./src/js/x/graphics/mipmap.js");
/* harmony import */ var _material_js__WEBPACK_IMPORTED_MODULE_12__ = __webpack_require__(/*! ./material.js */ "./src/js/homeworld2/material.js");














class ObjectFile
{
    static get weight(){ return 100; }

    static load(path, name, application)
    {
        return new _x_core_command_js__WEBPACK_IMPORTED_MODULE_8__["default"]((resolve, reject) => {
            let w = new Worker('/xgraphics/js/homeworld2/object.unpack.js');
            let o = new _obj_js__WEBPACK_IMPORTED_MODULE_0__["default"](name, 0, 1);
            let current = application.__current;

            w.postMessage({path});
            w.onmessage = (event) => {
                if(event.data.current && event.data.total)
                {
                    application.__current = current + (event.data.current/event.data.total) * ObjectFile.weight;
//                    console.log(application.__current);
                }
                if(event.data.version)
                {
//                    console.log("version");
                    o.__version = event.data.version;
                }
                else if(event.data.category)
                {
//                    console.log("category");
                    o.__category = event.data.category;
                }
                else if(event.data.material)
                {
                    o.materials.push(new _material_js__WEBPACK_IMPORTED_MODULE_12__["default"](event.data.material.name, event.data.material.shader, event.data.material.diffuse, event.data.material.glow));
                }
                else if(event.data.texture)
                {
                    // console.log("texture");
                    let texture = new _x_graphics_texture_js__WEBPACK_IMPORTED_MODULE_10__["default"](event.data.texture.name, event.data.texture.format);

                    event.data.texture.data.forEach(o => {
                        let mipmap = new _x_graphics_mipmap_js__WEBPACK_IMPORTED_MODULE_11__["default"](o.width, o.height, o.data);
                        texture.push(mipmap);
                    });

                    o.textures.push(texture);

                    // o.textures.set(event.data.texture.name, texture);
                }
                else if(event.data.multimesh)
                {
//                    console.log("multimesh");
                    let multimesh = new _multimesh_js__WEBPACK_IMPORTED_MODULE_1__["default"](event.data.multimesh.name, event.data.multimesh.parent, _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_5__["default"].enable);
                    event.data.multimesh.children.forEach(_singlemesh => {
                        let singlemesh = new _singlemesh_js__WEBPACK_IMPORTED_MODULE_3__["default"](_singlemesh.level, multimesh.status);
                        _singlemesh.primitives.forEach(_primitive => {
                            let primitive = new _primitive_js__WEBPACK_IMPORTED_MODULE_4__["default"]("", _singlemesh.level);
                            primitive.target = _x_graphics_buffer_js__WEBPACK_IMPORTED_MODULE_6__["default"].targetFromStr(_primitive.target);
                            primitive.usage = _x_graphics_buffer_js__WEBPACK_IMPORTED_MODULE_6__["default"].usageFromStr(_primitive.usage);
                            primitive.mode = _x_graphics_vertices_js__WEBPACK_IMPORTED_MODULE_7__["default"].modeFromStr(_primitive.mode);
                            primitive.material = o.material(_primitive.material);
                            primitive.texture = o.texture(primitive.material.diffuse);
                            primitive.program = application.programs.get(primitive.material.shader);
                            // console.log("program", primitive.program);
                            primitive.vertices.set(_primitive.vertices);
                            primitive.buffer.data = _primitive.data;
                            primitive.indices = _primitive.indices;
                            singlemesh.add(primitive);
                        });
                        multimesh.singlemesh.set(singlemesh.level, singlemesh);
                    });
                    o.multimesh.set(multimesh.name, multimesh);
                }
                else if(event.data.goblinmesh)
                {
//                    console.log("goblinmesh");
                    let goblinmesh = new _goblinmesh_js__WEBPACK_IMPORTED_MODULE_2__["default"](event.data.goblinmesh.name, event.data.goblinmesh.parent, _x_graphics_obj_js__WEBPACK_IMPORTED_MODULE_5__["default"].enable);
                    goblinmesh.singlemesh = new _singlemesh_js__WEBPACK_IMPORTED_MODULE_3__["default"](event.data.goblinmesh.singlemesh.level, goblinmesh.status);
                    event.data.goblinmesh.singlemesh.primitives.forEach(_primitive => {
                        let primitive = new _primitive_js__WEBPACK_IMPORTED_MODULE_4__["default"]("", event.data.goblinmesh.singlemesh.level);
                        primitive.target = _x_graphics_buffer_js__WEBPACK_IMPORTED_MODULE_6__["default"].targetFromStr(_primitive.target);
                        primitive.usage = _x_graphics_buffer_js__WEBPACK_IMPORTED_MODULE_6__["default"].usageFromStr(_primitive.usage);
                        primitive.mode = _x_graphics_vertices_js__WEBPACK_IMPORTED_MODULE_7__["default"].modeFromStr(_primitive.mode);
                        primitive.material = o.material(_primitive.material);
                        primitive.texture = o.texture(primitive.material.diffuse);
                        primitive.program = application.programs.get(primitive.material.shader);
                        // console.log("program", primitive.program);
                        primitive.vertices.set(_primitive.vertices);
                        primitive.buffer.data = _primitive.data;
                        primitive.indices = _primitive.indices;
                        goblinmesh.singlemesh.add(primitive);
                    });
                    o.goblinmesh.set(goblinmesh.name, goblinmesh);
                }
                else if(event.data.joints)
                {
//                    console.log("joints");
                    event.data.joints.forEach(_joint => {
                        let joint = new _joint_js__WEBPACK_IMPORTED_MODULE_9__["default"](_joint.name,
                                          _joint.parent,
                                          _joint.location,
                                          _joint.rotation,
                                          _joint.scale,
                                          _joint.axis,
                                          _joint.freedom);
                        o.joints.set(joint.name, joint);
                    });
                }
                else if(event.data.engineshape)
                {
//                    console.log("engineshape");
                    // console.log({engineshape: event.data.engineshape});
                }
                else if(event.data.engineburn)
                {
//                    console.log("engineburn");
                    // console.log({engineburn: event.data.engineburn});
                }
                else if(event.data.navlights)
                {
//                    console.log("navlights");
                    // console.log({navlights: event.data.navlights});
                }
                else if(event.data.marker)
                {
//                    console.log("marker");
                    // console.log({marker: event.data.marker});
                }
                else if(event.data.boundary)
                {
//                    console.log("boundary");
                    // console.log({boundary: event.data.boundary});
                }
                else if(event.data.collision)
                {
                    //console.log("collision");
                    // console.log({collision: event.data.collision});
                }
                else if(event.data.basicmesh)
                {
                    // console.log("basicmesh");
                    // console.log({basicmesh: event.data.basicmesh});
                }
                else if(event.data.information)
                {
                    //console.log("information");
                    // console.log({information: event.data.information});
                }
                else if(event.data.finish)
                {
                    if(event.data.error)
                    {
                        w.terminate();
                        w = null;
                        reject(new Error(event.data.error));
                    }
                    else
                    {
                        console.log("finish");
                        o.joints.forEach(joint => {
                            if(joint.parent === '')
                            {
                                o.root = joint;
                            }
                            else
                            {
                                let parent = o.joints.get(joint.parent);
                                parent.children.set(joint.name, joint);
                            }
                        });
                        o.multimesh.forEach(multimesh => {
                            let parent = o.joints.get(multimesh.parent);
                            parent.objects.push(multimesh);
                        });
                        o.goblinmesh.forEach(goblinmesh => {
                            let parent = o.joints.get(goblinmesh.parent);
                            parent.objects.push(goblinmesh);
                        });
                        w.terminate();
                        w = null;

                        application.__current = current + ObjectFile.weight;

                        application.objects.set(o.name, o);
                        resolve(o);
                    }
                }
            };
        }, ObjectFile.weight);
    }
}


/***/ }),

/***/ "./src/js/homeworld2/primitive.js":
/*!****************************************!*\
  !*** ./src/js/homeworld2/primitive.js ***!
  \****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Homeworld2Primitive; });
/* harmony import */ var _x_graphics_primitive_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/primitive.js */ "./src/js/x/graphics/primitive.js");
/* harmony import */ var _x_graphics_indices_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../x/graphics/indices.js */ "./src/js/x/graphics/indices.js");



class Homeworld2Primitive extends _x_graphics_primitive_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(name, level)
    {
        super(name, level, null);

        this.__material = null;
        this.__texture = null;
    }

    bind(application, name, value, model, level)
    {
        const gl = application.gl;

        if(!super.bind(application, name, value, model, level))
        {
            if(name == "textureSampler")
            {
                gl.activeTexture(gl.TEXTURE0);
                gl.bindTexture(gl.TEXTURE_2D, this.__texture.id);
                gl.uniform1i(value, 0);
            }
            else
            {
                throw new Error();
            }
        }
    }

    get name() { return this.__name; }
    get vertices() { return this.__vertices; }
    get buffer(){ return this.__buffer; }
    get program() { return this.__program; }
    get material(){ return this.__material; }
    get texture(){ return this.__texture; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set indices(v){ this.__indices = new _x_graphics_indices_js__WEBPACK_IMPORTED_MODULE_1__["default"](v); }
    set status(v){ this.__status = v; }
    set program(v){ this.__program = v; }
    set material(v){ this.__material = v; }
    set texture(v){ this.__texture = v; }
}


/***/ }),

/***/ "./src/js/homeworld2/reference.js":
/*!****************************************!*\
  !*** ./src/js/homeworld2/reference.js ***!
  \****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Homeworld2Reference; });
/* harmony import */ var _x_graphics_reference_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../x/graphics/reference.js */ "./src/js/x/graphics/reference.js");
/* harmony import */ var _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../x/graphics/matrix.js */ "./src/js/x/graphics/matrix.js");



class Homeworld2Reference extends _x_graphics_reference_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(name, location, rotation, scale, axis)
    {
        super(name, null, location, rotation, scale, axis);
    }

    render(application, model, level)
    {
        const gl = application.gl;

        this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].translate(model, this.__location);
        if(this.__axis[0] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[0], [1, 0, 0, 0]);
        }
        if(this.__axis[1] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[1], [0, 1, 0, 0]);
        }
        if(this.__axis[2] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[2], [0, 0, 1, 0]);
        }

        if(this.__rotation[1] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, (this.__location[0] > 0 ? this.__rotation[1] : -this.__rotation[1]), [1, 0, 0, 0]);
        }
        if(this.__rotation[0] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[0], [0, 1, 0, 0]);
        }
        if(this.__rotation[2] !== 0)
        {
            this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[2], [0, 0, 1, 0]);
        }

        this.__model = _x_graphics_matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].scale(this.__model, this.__scale);

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



class Singlemesh extends _x_graphics_complex_js__WEBPACK_IMPORTED_MODULE_0__["default"]
{
    constructor(level, status)
    {
        super("", level, status);
    }

    get level(){ return this.__level; }

    set status(v)
    {
        this.__status = v;
        this.__children.forEach(o => o.status = v);
    }
}


/***/ }),

/***/ "./src/js/x.js":
/*!*********************!*\
  !*** ./src/js/x.js ***!
  \*********************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./x/graphics/application.js */ "./src/js/x/graphics/application.js");
/* harmony import */ var _homeworld2_object_file_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./homeworld2/object.file.js */ "./src/js/homeworld2/object.file.js");
/* harmony import */ var _x_graphics_vertex_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./x/graphics/vertex.js */ "./src/js/x/graphics/vertex.js");
/* harmony import */ var _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./x/graphics/shader.js */ "./src/js/x/graphics/shader.js");
/* harmony import */ var _x_graphics_program_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./x/graphics/program.js */ "./src/js/x/graphics/program.js");
/* harmony import */ var _x_graphics_reference_js__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./x/graphics/reference.js */ "./src/js/x/graphics/reference.js");
/* harmony import */ var _x_graphics_primitives_triangle_js__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ./x/graphics/primitives/triangle.js */ "./src/js/x/graphics/primitives/triangle.js");
/* harmony import */ var _x_graphics_primitives_rectangle_js__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ./x/graphics/primitives/rectangle.js */ "./src/js/x/graphics/primitives/rectangle.js");
/* harmony import */ var _x_graphics_primitives_simple_loading_box_js__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! ./x/graphics/primitives/simple.loading.box.js */ "./src/js/x/graphics/primitives/simple.loading.box.js");
/* harmony import */ var _x_core_command_js__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! ./x/core/command.js */ "./src/js/x/core/command.js");










var __simple_fragment_code = "void main(){\n    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n}";
var __simple_vertex_code = "attribute vec4 vertexPosition;\n\nvoid main(){\n    gl_Position = vertexPosition;\n}";
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].shader(new _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"]("simple fragment", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].fragment, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, __simple_fragment_code));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].shader(new _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"]("simple vertex", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].vertex, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, __simple_vertex_code));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].program(new _x_graphics_program_js__WEBPACK_IMPORTED_MODULE_4__["default"]("simple", ["simple fragment", "simple vertex"], [], ["vertexPosition", "vertexNormal"]));
var __loading_simple_box_fragment_code = "precision mediump float;\nuniform float progress;\nuniform float idx;\nvarying vec2 vTexCoord;\n\nvoid main() {\n    if(vTexCoord.x < progress)\n    {\n        if(vTexCoord.x < idx)\n        {\n            gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);\n        }\n        else\n        {\n            gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n        }\n    }\n    else\n    {\n        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n    }\n}";
var __loading_simple_box_vertex_code = "attribute vec4 vertexPosition;\nprecision mediump float;\nuniform float progress;\nuniform float idx;\nvarying vec2 vTexCoord;\n\nvoid main(){\n    gl_PointSize = 1.0;\n    gl_Position = vertexPosition;\n\n    vTexCoord = vertexPosition.xy;\n}";
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].shader(new _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"]("loading simple box fragment", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].fragment, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, __loading_simple_box_fragment_code));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].shader(new _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"]("loading simple box vertex", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].vertex, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, __loading_simple_box_vertex_code));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].program(new _x_graphics_program_js__WEBPACK_IMPORTED_MODULE_4__["default"]("loading simple box", ["loading simple box fragment", "loading simple box vertex"], ["progress", "idx"], ["vertexPosition", "vertexNormal"]));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].object(new _x_graphics_primitives_triangle_js__WEBPACK_IMPORTED_MODULE_6__["default"]("triangle", 0, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].programs.get("simple")));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].object(new _x_graphics_primitives_rectangle_js__WEBPACK_IMPORTED_MODULE_7__["default"]("rectangle", 0, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].programs.get("simple")));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].object(new _x_graphics_primitives_simple_loading_box_js__WEBPACK_IMPORTED_MODULE_8__["default"]("loading", 0, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].programs.get("loading simple box"), {
  scale: [300 / _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].width, 20 / _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].height, 1.0, 0.0]
}));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].reference(new _x_graphics_reference_js__WEBPACK_IMPORTED_MODULE_5__["default"]("loading", _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].objects.get("loading")));
_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].loading([_x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].load("/xgraphics/shader/standard.fragment.shader", "standard fragment", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].fragment, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].load("/xgraphics/shader/standard.vertex.shader", "standard vertex", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].vertex, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].load("/xgraphics/res/homeworld2/shader/ship/fragment.shader", "homeworld2 ship fragment", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].fragment, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].load("/xgraphics/res/homeworld2/shader/ship/vertex.shader", "homeworld2 ship vertex", _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].vertex, _x_graphics_shader_js__WEBPACK_IMPORTED_MODULE_3__["default"].none, _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _x_graphics_program_js__WEBPACK_IMPORTED_MODULE_4__["default"].load("standard", ["standard fragment", "standard vertex"], ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength"], ["vertexPosition", "vertexNormal"], _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _x_graphics_program_js__WEBPACK_IMPORTED_MODULE_4__["default"].load("ship", ["homeworld2 ship fragment", "homeworld2 ship vertex"], ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength", "textureSampler"], ["vertexPosition", "vertexNormal", "vertexUV"], _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"]), _homeworld2_object_file_js__WEBPACK_IMPORTED_MODULE_1__["default"].load("/xgraphics/sample.hod", "sample", _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"])]).then(function (o) {
  _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].run(function () {
    _x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].reference(_x_graphics_application_js__WEBPACK_IMPORTED_MODULE_0__["default"].objects.get("sample").build("sample")); // application.reference(new Reference("sample", ));

    console.log("running");
  });
  console.log("success");
})["catch"](function (e) {
  console.log(e);
});
console.log("hello world");

/***/ }),

/***/ "./src/js/x/core/command.js":
/*!**********************************!*\
  !*** ./src/js/x/core/command.js ***!
  \**********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Command; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Command = /*#__PURE__*/function () {
  function Command(func, weight) {
    _classCallCheck(this, Command);

    this.__func = func;
    this.__weight = weight;
  }

  _createClass(Command, [{
    key: "call",
    value: function call() {
      var _this = this;

      return new Promise(function (resolve, reject) {
        _this.__func(resolve, reject);
      });
    }
  }, {
    key: "weight",
    get: function get() {
      return this.__weight;
    }
  }]);

  return Command;
}();



/***/ }),

/***/ "./src/js/x/core/executor.js":
/*!***********************************!*\
  !*** ./src/js/x/core/executor.js ***!
  \***********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Executor; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Executor = /*#__PURE__*/function () {
  function Executor() {
    _classCallCheck(this, Executor);

    this.__queue = null;
    this.__total = 0;
    this.__current = 0;
    this.__index = 0;
  }

  _createClass(Executor, [{
    key: "dispatch",
    value: function dispatch(command) {
      if (command) {
        this.__queue = this.__queue || [];

        this.__queue.push(command);

        this.__total = this.__total + command.weight;
      }
    }
  }, {
    key: "call",
    value: function call(resolve, reject) {
      var _this = this;

      var results = [];

      if (this.__index < this.__queue.length) {
        this.__queue[this.__index].call().then(function (o) {
          results.push(o);
          _this.__index++;

          _this.call(resolve, reject);
        })["catch"](function (e) {
          return reject(e);
        });
      } else {
        resolve(results);
      }
    }
  }, {
    key: "execute",
    value: function execute() {
      var _this2 = this;

      return new Promise(function (resolve, reject) {
        return _this2.call(resolve, reject);
      });
      /**
      console.log("execute");
      return new Promise((resolve, reject) => {
          if(this.__index < this.__queue.length)
          {
           }
      });
      */
      // if(this.__queue)
      // {
      //     return Promise.all(this.__queue);
      // }
      // return Promise.reject(new Error());
    }
  }]);

  return Executor;
}();



/***/ }),

/***/ "./src/js/x/graphics/application.js":
/*!******************************************!*\
  !*** ./src/js/x/graphics/application.js ***!
  \******************************************/
/*! exports provided: Application, default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "Application", function() { return Application; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return application; });
/* harmony import */ var _core_executor_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../core/executor.js */ "./src/js/x/core/executor.js");
/* harmony import */ var _camera_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./camera.js */ "./src/js/x/graphics/camera.js");
/* harmony import */ var _projection_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./projection.js */ "./src/js/x/graphics/projection.js");
/* harmony import */ var _light_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./light.js */ "./src/js/x/graphics/light.js");
/* harmony import */ var _surface_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./surface.js */ "./src/js/x/graphics/surface.js");
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./matrix.js */ "./src/js/x/graphics/matrix.js");
/* harmony import */ var _core_command_js__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ../core/command.js */ "./src/js/x/core/command.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }








var application = null;
var Application = /*#__PURE__*/function (_Executor) {
  _inherits(Application, _Executor);

  _createClass(Application, null, [{
    key: "__loading",
    value: function __loading() {
      // application.__progress += 0.01;
      application.__progress = application.__current / application.__total; // console.log(application.current);

      if (application.finish) {
        console.log("end loading");
        application.__references = new Map();
        application.render();

        if (application.__defer) {
          application.__defer.call();
        }
      } else {
        application.render();
        setTimeout(Application.__loading, 1000 / 30);
      }
    }
  }]);

  function Application() {
    var _this;

    _classCallCheck(this, Application);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(Application).call(this));
    _this.__x = 0;
    _this.__y = 0;
    _this.__name = "";
    _this.__shaders = new Map();
    _this.__programs = new Map();
    _this.__surface = null;
    _this.__objects = new Map();
    _this.__references = new Map();
    _this.__major = 4;
    _this.__minor = 5;
    _this.__mode = 0;
    _this.__progress = 0;
    _this.__finish = false;
    _this.__defer = null;

    if (!_this.__surface) {
      var canvas = document.createElement("canvas");
      canvas.width = document.body.clientWidth;
      canvas.height = document.body.clientHeight;
      document.body.appendChild(canvas);
      _this.__surface = new _surface_js__WEBPACK_IMPORTED_MODULE_4__["default"](canvas);

      _this.__surface.initialize();
    }

    return _this;
  }

  _createClass(Application, [{
    key: "run",
    value: function run(func) {
      var _this2 = this;

      this.__defer = new _core_command_js__WEBPACK_IMPORTED_MODULE_6__["default"](function (resolve, reject) {
        _this2.__programs.forEach(function (program) {
          return program.load(_this2);
        });

        _this2.__objects.forEach(function (object) {
          return object.load(_this2);
        });

        func();

        _this2.render();
      }, 1);

      if (this.__finish) {
        this.__defer.call();

        this.__defer = null;
        console.log("defer call");
      }
    }
  }, {
    key: "loading",
    value: function loading(commands) {
      var _this3 = this;

      this.__programs.forEach(function (program) {
        return program.load(_this3);
      });

      this.__objects.forEach(function (object) {
        return object.load(_this3);
      });

      commands.forEach(function (command) {
        _this3.dispatch(command);
      });
      console.log("total", this.__total); // this.render();

      Application.__loading();

      return this.execute();
    }
  }, {
    key: "render",
    value: function render() {
      // console.log("application render");
      this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
      this.gl.clearColor(this.background[0], this.background[1], this.background[2], this.background[3]);
      this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.COLOR_DEPTH_BIT);

      this.__references.forEach(function (reference, name) {
        // console.log("render", name);
        reference.render(application, _matrix_js__WEBPACK_IMPORTED_MODULE_5__["default"].identity(), 0);
      });
    }
  }, {
    key: "shader",
    value: function shader(o) {
      this.__shaders.set(o.name, o);

      return o;
    }
  }, {
    key: "program",
    value: function program(o) {
      this.__programs.set(o.name, o);

      return o;
    }
  }, {
    key: "object",
    value: function object(o) {
      this.__objects.set(o.name, o);

      return o;
    }
  }, {
    key: "reference",
    value: function reference(o) {
      this.__references.set(o.name, o);

      return o;
    }
  }, {
    key: "gl",
    get: function get() {
      return this.__surface.gl;
    }
  }, {
    key: "extension",
    get: function get() {
      return this.__surface.extension;
    }
  }, {
    key: "programs",
    get: function get() {
      return this.__programs;
    }
  }, {
    key: "shaders",
    get: function get() {
      return this.__shaders;
    }
  }, {
    key: "objects",
    get: function get() {
      return this.__objects;
    }
  }, {
    key: "background",
    get: function get() {
      return this.__surface.background;
    }
  }, {
    key: "light",
    get: function get() {
      return this.__surface.light;
    }
  }, {
    key: "camera",
    get: function get() {
      return this.__surface.camera;
    }
  }, {
    key: "projection",
    get: function get() {
      return this.__surface.projection;
    }
  }, {
    key: "progress",
    get: function get() {
      return this.__progress;
    }
  }, {
    key: "finish",
    get: function get() {
      return this.__finish;
    },
    set: function set(v) {
      this.__finish = v;
    }
  }, {
    key: "width",
    get: function get() {
      return this.__surface.width;
    }
  }, {
    key: "height",
    get: function get() {
      return this.__surface.height;
    }
  }]);

  return Application;
}(_core_executor_js__WEBPACK_IMPORTED_MODULE_0__["default"]);
application = new Application();


/***/ }),

/***/ "./src/js/x/graphics/buffer.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/buffer.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Buffer; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Buffer = /*#__PURE__*/function () {
  _createClass(Buffer, null, [{
    key: "targetFromStr",
    value: function targetFromStr(s) {
      if (s === "array") {
        s = Buffer.array;
      } else {
        throw new Error();
      }

      return s;
    }
  }, {
    key: "usageFromStr",
    value: function usageFromStr(s) {
      if (s[0] === "statical") {
        s[0] = Buffer.statical;
      } else {
        throw new Error();
      }

      if (s[1] === "draw") {
        s[1] = Buffer.draw;
      } else {
        throw new Error();
      }

      return s;
    }
  }, {
    key: "getTarget",
    value: function getTarget(gl, target) {
      switch (target) {
        case Buffer.array:
          return gl.ARRAY_BUFFER;

        default:
          throw new Error();
      }
    }
  }, {
    key: "getUsage",
    value: function getUsage(gl, usage) {
      switch (usage[0]) {
        case Buffer.statical:
          switch (usage[1]) {
            case Buffer.draw:
              return gl.STATIC_DRAW;

            default:
              throw new Error();
          }

        default:
          throw new Error();
      }
    }
  }, {
    key: "none",
    get: function get() {
      return 0;
    }
  }, {
    key: "array",
    get: function get() {
      return 1;
    }
  }, {
    key: "atomic_counter",
    get: function get() {
      return 2;
    }
  }, {
    key: "copy_read",
    get: function get() {
      return 3;
    }
  }, {
    key: "copy_write",
    get: function get() {
      return 4;
    }
  }, {
    key: "dispatch_indirect",
    get: function get() {
      return 5;
    }
  }, {
    key: "draw_indirect",
    get: function get() {
      return 6;
    }
  }, {
    key: "element_array",
    get: function get() {
      return 7;
    }
  }, {
    key: "pixel_pack",
    get: function get() {
      return 8;
    }
  }, {
    key: "pixel_unpack",
    get: function get() {
      return 9;
    }
  }, {
    key: "query",
    get: function get() {
      return 10;
    }
  }, {
    key: "shader_storage",
    get: function get() {
      return 11;
    }
  }, {
    key: "texture",
    get: function get() {
      return 12;
    }
  }, {
    key: "transform_feedback",
    get: function get() {
      return 13;
    }
  }, {
    key: "uniform",
    get: function get() {
      return 14;
    }
  }, {
    key: "stream",
    get: function get() {
      return 1;
    }
  }, {
    key: "statical",
    get: function get() {
      return 2;
    }
  }, {
    key: "dynamical",
    get: function get() {
      return 3;
    }
  }, {
    key: "draw",
    get: function get() {
      return 1;
    }
  }, {
    key: "read",
    get: function get() {
      return 2;
    }
  }, {
    key: "copy",
    get: function get() {
      return 3;
    }
  }]);

  function Buffer() {
    _classCallCheck(this, Buffer);

    this.__data = null;
    this.__target = Buffer.none;
    this.__usage = [Buffer.none, Buffer.none];
    this.__id = 0;
  }

  _createClass(Buffer, [{
    key: "load",
    value: function load(application) {
      var gl = application.gl;

      if (!this.__id) {
        this.__id = gl.createBuffer();
        gl.bindBuffer(Buffer.getTarget(gl, this.__target), this.__id);
        gl.bufferData(Buffer.getTarget(gl, this.__target), this.__data, Buffer.getUsage(gl, this.__usage));
      }
    }
  }, {
    key: "unload",
    value: function unload(application) {
      var gl = application.gl;
      console.log("unload buffer");
    }
  }, {
    key: "bind",
    value: function bind(application) {
      var gl = application.gl;
      gl.bindBuffer(Buffer.getTarget(gl, this.__target), this.__id);
    }
  }, {
    key: "target",
    set: function set(v) {
      this.__target = v;
    }
  }, {
    key: "usage",
    set: function set(v) {
      this.__usage = v;
    }
  }, {
    key: "data",
    set: function set(v) {
      this.__data = v;
    },
    get: function get() {
      return this.__data;
    }
  }, {
    key: "size",
    get: function get() {
      return this.__data ? this.__data.length : 0;
    }
  }]);

  return Buffer;
}();



/***/ }),

/***/ "./src/js/x/graphics/camera.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/camera.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Camera; });
/* harmony import */ var _vector_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./vector.js */ "./src/js/x/graphics/vector.js");
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./matrix.js */ "./src/js/x/graphics/matrix.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }




var Camera = /*#__PURE__*/function () {
  function Camera(location, center, up) {
    _classCallCheck(this, Camera);

    this.__center = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(center, 0.0);
    this.__up = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(up, 0.0);
    this.__location = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(location, 1.0);
    this.__matrix = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].lookat(this.__location, this.__center, this.__up);
  }

  _createClass(Camera, [{
    key: "matrix",
    get: function get() {
      return this.__matrix;
    }
  }, {
    key: "location",
    get: function get() {
      return this.__location;
    }
  }]);

  return Camera;
}();



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

/***/ "./src/js/x/graphics/indices.js":
/*!**************************************!*\
  !*** ./src/js/x/graphics/indices.js ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Indices; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Indices = /*#__PURE__*/function () {
  function Indices(indices) {
    _classCallCheck(this, Indices);

    this.__data = null;
    this.__id = null;
    this.__indices = indices;
  }

  _createClass(Indices, [{
    key: "load",
    value: function load(application) {
      var gl = application.gl;

      if (this.__indices) {
        if (!this.__id) {
          if (!this.__data) {
            this.__data = new Uint16Array(this.__indices);
          }

          this.__id = gl.createBuffer();
          gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.__id);
          gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.__data, gl.STATIC_DRAW);
        }
      }
    }
  }, {
    key: "unload",
    value: function unload(application) {
      var gl = application.gl;
    }
  }, {
    key: "bind",
    value: function bind(application) {
      var gl = application.gl;
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.__id);
    }
  }, {
    key: "size",
    get: function get() {
      return this.__indices ? this.__indices.length : 0;
    }
  }]);

  return Indices;
}();



/***/ }),

/***/ "./src/js/x/graphics/light.js":
/*!************************************!*\
  !*** ./src/js/x/graphics/light.js ***!
  \************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Light; });
/* harmony import */ var _vector_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./vector.js */ "./src/js/x/graphics/vector.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Light = /*#__PURE__*/function () {
  function Light(location, color, ambient) {
    _classCallCheck(this, Light);

    this.__location = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(location, 1);
    this.__color = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(color, 1);
    this.__ambient = ambient || 1;
  }

  _createClass(Light, [{
    key: "location",
    get: function get() {
      return this.__location;
    }
  }, {
    key: "color",
    get: function get() {
      return this.__color;
    }
  }, {
    key: "ambient",
    get: function get() {
      return this.__ambient;
    }
  }]);

  return Light;
}();



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

/***/ "./src/js/x/graphics/mipmap.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/mipmap.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Mipmap; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Mipmap = /*#__PURE__*/function () {
  function Mipmap(width, height, data) {
    _classCallCheck(this, Mipmap);

    this.__id;
    this.__width = width;
    this.__height = height;
    this.__data = data;
  }

  _createClass(Mipmap, [{
    key: "width",
    get: function get() {
      return this.__width;
    }
  }, {
    key: "height",
    get: function get() {
      return this.__height;
    }
  }, {
    key: "data",
    get: function get() {
      return this.__data;
    }
  }]);

  return Mipmap;
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

/***/ "./src/js/x/graphics/primitive.js":
/*!****************************************!*\
  !*** ./src/js/x/graphics/primitive.js ***!
  \****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Primitive; });
/* harmony import */ var _obj_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./obj.js */ "./src/js/x/graphics/obj.js");
/* harmony import */ var _vertices_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./vertices.js */ "./src/js/x/graphics/vertices.js");
/* harmony import */ var _buffer_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./buffer.js */ "./src/js/x/graphics/buffer.js");
/* harmony import */ var _indices_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./indices.js */ "./src/js/x/graphics/indices.js");
/* harmony import */ var _vertex_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./vertex.js */ "./src/js/x/graphics/vertex.js");
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./matrix.js */ "./src/js/x/graphics/matrix.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }








var Primitive = /*#__PURE__*/function (_Obj) {
  _inherits(Primitive, _Obj);

  function Primitive(name, level, program) {
    var _this;

    _classCallCheck(this, Primitive);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(Primitive).call(this, name, level));
    _this.__vertices = new _vertices_js__WEBPACK_IMPORTED_MODULE_1__["default"]();
    _this.__buffer = new _buffer_js__WEBPACK_IMPORTED_MODULE_2__["default"]();
    _this.__program = program;
    _this.__indices = new _indices_js__WEBPACK_IMPORTED_MODULE_3__["default"]();
    return _this;
  }

  _createClass(Primitive, [{
    key: "push",
    value: function push(o) {
      this.__vertices.push(o);
    }
  }, {
    key: "load",
    value: function load(application) {
      if (!this.__load) {
        if (!this.__buffer.size) {
          this.__vertices.serialize(this.__buffer);
        }

        this.__program.load(application);

        this.__indices.load(application);

        this.__vertices.load(application);

        this.__buffer.load(application);

        this.__load = true;
      }
    }
  }, {
    key: "unload",
    value: function unload(application) {
      if (this.__load) {
        this.__program.unload(application);

        this.__indices.unload(application);

        this.__vertices.unload(application);

        this.__buffer.unload(application);

        this.__load = false;
      }
    }
  }, {
    key: "bind",
    value: function bind(application, name, value, model, level) {
      var gl = application.gl;

      if (name === "mvp") {
        var camera = application.camera;
        var projection = application.projection; // console.log(model)

        var mvp = _matrix_js__WEBPACK_IMPORTED_MODULE_5__["default"].multiply(_matrix_js__WEBPACK_IMPORTED_MODULE_5__["default"].multiply(model, camera.matrix), projection.matrix);
        gl.uniformMatrix4fv(value, false, new Float32Array(mvp));
        return true;
      } else if (name === "cameraPos") {
        var _camera = application.camera;
        gl.uniform4fv(value, _camera.location);
        return true;
      } else if (name === "lightColor") {
        var light = application.light;
        gl.uniform4fv(value, light.color);
        return true;
      } else if (name === "lightPos") {
        var _light = application.light;
        gl.uniform4fv(value, _light.location);
        return true;
      } else if (name === "ambientStrength") {
        var _light2 = application.light;
        gl.uniform1f(value, _light2.ambient);
        return true;
      } else {
        return false;
      }
    }
  }, {
    key: "render",
    value: function render(application, model, level) {
      var _this2 = this;

      if (this.__level === level) {
        var gl = application.gl;
        gl.useProgram(this.__program.id);

        this.__program.uniforms.forEach(function (value, name) {
          _this2.bind(application, name, value, model, level);
        });

        this.__program.attributes.forEach(function (value, name) {
          if (value >= 0) {
            gl.enableVertexAttribArray(value);

            _this2.buffer.bind(application);

            if (name === "vertexPosition") {
              gl.vertexAttribPointer(value, 4, gl.FLOAT, false, _vertex_js__WEBPACK_IMPORTED_MODULE_4__["default"].stride, 0);
            } else if (name === "vertexNormal") {
              gl.vertexAttribPointer(value, 4, gl.FLOAT, false, _vertex_js__WEBPACK_IMPORTED_MODULE_4__["default"].stride, 4 * 4);
            } else if (name === "vertexUV") {
              gl.vertexAttribPointer(value, 4, gl.FLOAT, false, _vertex_js__WEBPACK_IMPORTED_MODULE_4__["default"].stride, 12 * 4);
            }
          }
        });

        this.buffer.bind(application);

        if (this.__indices.size) {
          this.__indices.bind(application); // TODO: REMOVE TRIANGLES


          gl.drawElements(gl.TRIANGLES, this.__indices.size, gl.UNSIGNED_SHORT, 0);
        } else {
          // TODO: REMOVE TRIANGLES
          gl.drawArrays(gl.TRIANGLES, 0, this.__vertices.size);
        }
      }
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "vertices",
    get: function get() {
      return this.__vertices;
    }
  }, {
    key: "buffer",
    get: function get() {
      return this.__buffer;
    }
  }, {
    key: "program",
    get: function get() {
      return this.__program;
    },
    set: function set(v) {
      this.__program = v;
    }
  }, {
    key: "mode",
    set: function set(v) {
      this.__vertices.mode = v;
    }
  }, {
    key: "target",
    set: function set(v) {
      this.__buffer.target = v;
    }
  }, {
    key: "usage",
    set: function set(v) {
      this.__buffer.usage = v;
    }
  }, {
    key: "indices",
    set: function set(v) {
      this.__indices = new _indices_js__WEBPACK_IMPORTED_MODULE_3__["default"](v);
    }
  }, {
    key: "status",
    set: function set(v) {
      this.__status = v;
    }
  }]);

  return Primitive;
}(_obj_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/primitives/rectangle.js":
/*!***************************************************!*\
  !*** ./src/js/x/graphics/primitives/rectangle.js ***!
  \***************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Rectangle; });
/* harmony import */ var _primitive_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../primitive.js */ "./src/js/x/graphics/primitive.js");
/* harmony import */ var _vertex_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../vertex.js */ "./src/js/x/graphics/vertex.js");
/* harmony import */ var _vertices_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../vertices.js */ "./src/js/x/graphics/vertices.js");
/* harmony import */ var _buffer_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ../buffer.js */ "./src/js/x/graphics/buffer.js");
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ../matrix.js */ "./src/js/x/graphics/matrix.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }







var Rectangle = /*#__PURE__*/function (_Primitive) {
  _inherits(Rectangle, _Primitive);

  _createClass(Rectangle, null, [{
    key: "load",
    value: function load(name, program, application, options) {
      return new Promise(function (resolve, reject) {
        var o = new Rectangle(name, 0, application.programs.get(program), options);
        o.serialize();
        application.object(o);
        resolve(o);
      });
    }
  }]);

  function Rectangle(name, level, program, options) {
    var _this;

    _classCallCheck(this, Rectangle);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(Rectangle).call(this, name, level, program));
    _this.mode = _vertices_js__WEBPACK_IMPORTED_MODULE_2__["default"].triangle;
    _this.target = _buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].array;
    _this.usage = [_buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].statical, _buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].draw];

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([-0.5, 0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0.5, 0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0.5, -0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0.5, -0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([-0.5, -0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([-0.5, 0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    if (options) {
      if (options.scale) {
        _this.__vertices.each(function (vertex) {
          vertex.location = _matrix_js__WEBPACK_IMPORTED_MODULE_4__["default"].vectorMultiply(_matrix_js__WEBPACK_IMPORTED_MODULE_4__["default"].scale(_matrix_js__WEBPACK_IMPORTED_MODULE_4__["default"].identity(), options.scale), vertex.location);
        });
      }
    }

    return _this;
  }

  _createClass(Rectangle, [{
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "program",
    get: function get() {
      return this.__program;
    },
    set: function set(o) {
      this.__program = o;
    }
  }, {
    key: "buffer",
    get: function get() {
      return this.__buffer;
    }
  }, {
    key: "mode",
    set: function set(v) {
      this.__vertices.mode = v;
    }
  }, {
    key: "target",
    set: function set(v) {
      this.__buffer.target = v;
    }
  }, {
    key: "usage",
    set: function set(v) {
      this.__buffer.usage = v;
    }
  }]);

  return Rectangle;
}(_primitive_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/primitives/simple.loading.box.js":
/*!************************************************************!*\
  !*** ./src/js/x/graphics/primitives/simple.loading.box.js ***!
  \************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return SimpleLoadingBox; });
/* harmony import */ var _rectangle_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./rectangle.js */ "./src/js/x/graphics/primitives/rectangle.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _get(target, property, receiver) { if (typeof Reflect !== "undefined" && Reflect.get) { _get = Reflect.get; } else { _get = function _get(target, property, receiver) { var base = _superPropBase(target, property); if (!base) return; var desc = Object.getOwnPropertyDescriptor(base, property); if (desc.get) { return desc.get.call(receiver); } return desc.value; }; } return _get(target, property, receiver || target); }

function _superPropBase(object, property) { while (!Object.prototype.hasOwnProperty.call(object, property)) { object = _getPrototypeOf(object); if (object === null) break; } return object; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }

// import Primitive from '../../../primitive.js';
 // import Vertex from '../../../vertex.js';
// import Vertices from '../../../vertices.js';
// import Buffer from '../../../buffer.js';
// import Matrix from '../../../matrix.js';

var SimpleLoadingBox = /*#__PURE__*/function (_Rectangle) {
  _inherits(SimpleLoadingBox, _Rectangle);

  _createClass(SimpleLoadingBox, null, [{
    key: "load",
    value: function load(name, program, application, options) {
      return new Promise(function (resolve, reject) {
        var o = new SimpleLoadingBox(name, 0, application.programs.get(program), options);
        o.serialize();
        application.object(o);
        resolve(o);
      });
    }
  }]);

  function SimpleLoadingBox(name, level, program, options) {
    var _this;

    _classCallCheck(this, SimpleLoadingBox);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(SimpleLoadingBox).call(this, name, level, program, options));
    _this.min = 0;
    _this.max = 0;
    _this.__progress = 0;
    _this.__current = 0;
    _this.__idx = 0;

    _this.__vertices.each(function (vertex) {
      _this.min = Math.min(vertex.location[0], _this.min);
      _this.max = Math.max(vertex.location[0], _this.max);
    });

    return _this;
  }

  _createClass(SimpleLoadingBox, [{
    key: "bind",
    value: function bind(application, name, value, model, level) {
      if (!_get(_getPrototypeOf(SimpleLoadingBox.prototype), "bind", this).call(this, application, name, value, model, level)) {
        var gl = application.gl;

        if (name === "progress") {
          var total = this.max - this.min;

          if (this.__current < application.progress) {
            this.__current += 0.01;
          }

          if (application.progress < this.__current) {
            this.__current = application.progress;
          }

          gl.uniform1f(value, this.min + this.__current * total);
        }

        if (name === "idx") {
          var _total = this.max - this.min;

          if (application.progress === this.__current) {
            this.__idx += 0.01;

            if (this.__current < this.__idx) {
              if (this.__current === 1) {
                application.finish = true; // application.current = 1;
              }

              this.__idx = 0;
            }
          }

          gl.uniform1f(value, this.min + this.__idx * _total);
        }
      }
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "program",
    get: function get() {
      return this.__program;
    },
    set: function set(o) {
      this.__program = o;
    }
  }, {
    key: "buffer",
    get: function get() {
      return this.__buffer;
    }
  }, {
    key: "mode",
    set: function set(v) {
      this.__vertices.mode = v;
    }
  }, {
    key: "target",
    set: function set(v) {
      this.__buffer.target = v;
    }
  }, {
    key: "usage",
    set: function set(v) {
      this.__buffer.usage = v;
    }
  }]);

  return SimpleLoadingBox;
}(_rectangle_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/primitives/triangle.js":
/*!**************************************************!*\
  !*** ./src/js/x/graphics/primitives/triangle.js ***!
  \**************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Triangle; });
/* harmony import */ var _primitive_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../primitive.js */ "./src/js/x/graphics/primitive.js");
/* harmony import */ var _vertex_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../vertex.js */ "./src/js/x/graphics/vertex.js");
/* harmony import */ var _vertices_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../vertices.js */ "./src/js/x/graphics/vertices.js");
/* harmony import */ var _buffer_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ../buffer.js */ "./src/js/x/graphics/buffer.js");
function _typeof(obj) { "@babel/helpers - typeof"; if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (call && (_typeof(call) === "object" || typeof call === "function")) { return call; } return _assertThisInitialized(self); }

function _assertThisInitialized(self) { if (self === void 0) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return self; }

function _getPrototypeOf(o) { _getPrototypeOf = Object.setPrototypeOf ? Object.getPrototypeOf : function _getPrototypeOf(o) { return o.__proto__ || Object.getPrototypeOf(o); }; return _getPrototypeOf(o); }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function"); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, writable: true, configurable: true } }); if (superClass) _setPrototypeOf(subClass, superClass); }

function _setPrototypeOf(o, p) { _setPrototypeOf = Object.setPrototypeOf || function _setPrototypeOf(o, p) { o.__proto__ = p; return o; }; return _setPrototypeOf(o, p); }






var Triangle = /*#__PURE__*/function (_Primitive) {
  _inherits(Triangle, _Primitive);

  _createClass(Triangle, null, [{
    key: "load",
    value: function load(name, program, application, options) {
      return new Promise(function (resolve, reject) {
        var o = new Triangle(name, 0, application.programs.get(program), options);
        o.serialize();
        application.object(o);
        resolve(o);
      });
    }
  }]);

  function Triangle(name, level, program, options) {
    var _this;

    _classCallCheck(this, Triangle);

    _this = _possibleConstructorReturn(this, _getPrototypeOf(Triangle).call(this, name, level, program));
    _this.mode = _vertices_js__WEBPACK_IMPORTED_MODULE_2__["default"].triangle;
    _this.target = _buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].array;
    _this.usage = [_buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].statical, _buffer_js__WEBPACK_IMPORTED_MODULE_3__["default"].draw];

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0.0, 0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([-0.5, -0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    _this.push(new _vertex_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0.5, -0.5, 0.0, 1.0], [0.0, 0.0, 1.0, 0.0]));

    if (options) {
      if (options.scale) {
        o.__vertices.each(function (vertex) {
          vertex.location = Matrix.vectorMultiply(Matrix.scale(Matrix.identity(), options.scale), vertex.location);
        });
      }
    }

    return _this;
  }

  _createClass(Triangle, [{
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "program",
    get: function get() {
      return this.__program;
    },
    set: function set(o) {
      this.__program = o;
    }
  }, {
    key: "buffer",
    get: function get() {
      return this.__buffer;
    }
  }, {
    key: "mode",
    set: function set(v) {
      this.__vertices.mode = v;
    }
  }, {
    key: "target",
    set: function set(v) {
      this.__buffer.target = v;
    }
  }, {
    key: "usage",
    set: function set(v) {
      this.__buffer.usage = v;
    }
  }]);

  return Triangle;
}(_primitive_js__WEBPACK_IMPORTED_MODULE_0__["default"]);



/***/ }),

/***/ "./src/js/x/graphics/program.js":
/*!**************************************!*\
  !*** ./src/js/x/graphics/program.js ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Program; });
/* harmony import */ var _core_command_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../core/command.js */ "./src/js/x/core/command.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Program = /*#__PURE__*/function () {
  _createClass(Program, null, [{
    key: "load",
    value: function load(name, shaders, uniforms, attributes, application) {
      return new _core_command_js__WEBPACK_IMPORTED_MODULE_0__["default"](function (resolve, reject) {
        var o = new Program(name, shaders, uniforms, attributes);

        if (!application.programs.get(name)) {
          application.programs.set(name, o);
          application.__current += Program.weight;
          resolve(o);
        } else {
          reject(new Error());
        }
      }, Program.weight);
    }
  }, {
    key: "weight",
    get: function get() {
      return 1;
    }
  }]);

  function Program(name, shaders, uniforms, attributes) {
    _classCallCheck(this, Program);

    this.__name = name;
    this.__id = 0;
    this.__shaders = shaders || new Array();
    this.__uniforms = uniforms ? new Map(uniforms.map(function (o) {
      return [o, null];
    })) : new Map();
    this.__attributes = attributes ? new Map(attributes.map(function (o) {
      return [o, null];
    })) : new Map();
  }

  _createClass(Program, [{
    key: "load",
    value: function load(application) {
      var _this = this;

      var gl = application.gl;

      if (!this.__id) {
        this.__id = gl.createProgram();

        this.__shaders.forEach(function (name) {
          var o = application.shaders.get(name);
          o.load(application);
          gl.attachShader(_this.__id, o.id);
        });

        gl.linkProgram(this.__id);

        if (gl.getProgramParameter(this.__id, gl.LINK_STATUS)) {
          this.__shaders.forEach(function (name) {
            var o = application.shaders.get(name);
            o.unload(application);
          });

          this.__attributes.forEach(function (value, name) {
            return _this.__attributes.set(name, gl.getAttribLocation(_this.__id, name));
          });

          this.__uniforms.forEach(function (value, name) {
            return _this.__uniforms.set(name, gl.getUniformLocation(_this.__id, name));
          });

          return this;
        } else {
          throw new Error();
        }
      }
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "id",
    get: function get() {
      return this.__id;
    }
  }, {
    key: "attributes",
    get: function get() {
      return this.__attributes;
    }
  }, {
    key: "uniforms",
    get: function get() {
      return this.__uniforms;
    }
  }]);

  return Program;
}();



/***/ }),

/***/ "./src/js/x/graphics/projection.js":
/*!*****************************************!*\
  !*** ./src/js/x/graphics/projection.js ***!
  \*****************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Projection; });
/* harmony import */ var _matrix_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./matrix.js */ "./src/js/x/graphics/matrix.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Projection = /*#__PURE__*/function () {
  function Projection(fovy, aspect, near, far) {
    _classCallCheck(this, Projection);

    // TODO: 0.01745329251994329576923690768489 TO CONST VARIABLE
    this.__fovy = fovy || 45 * 0.01745329251994329576923690768489;
    this.__aspect = aspect || 1;
    this.__near = near || 0.1;
    this.__far = far || 10000.0;
    this.__matrix = _matrix_js__WEBPACK_IMPORTED_MODULE_0__["default"].perspective(this.__fovy, this.__aspect, this.__near, this.__far);
  }

  _createClass(Projection, [{
    key: "matrix",
    get: function get() {
      return this.__matrix;
    }
  }]);

  return Projection;
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
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }




var Reference = /*#__PURE__*/function () {
  function Reference(name, object, location, rotation, scale, axis) {
    _classCallCheck(this, Reference);

    this.__name = name;
    this.__location = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(location, 0.0);
    this.__rotation = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(rotation, 0.0);
    this.__scale = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(scale || [1, 1, 1, 0], 0.0);
    this.__axis = _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(axis, 0.0);
    this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].identity();
    this.__level = 0;
    this.__objects = new Map();
    this.__children = new Map();

    if (object) {
      this.__objects.set(object.name, object);
    }
  }

  _createClass(Reference, [{
    key: "render",
    value: function render(application, model, level) {
      var _this = this;

      var gl = application.gl;
      this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].translate(model, this.__location);

      if (this.__axis[0] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[0], [1, 0, 0, 0]);
      }

      if (this.__axis[1] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[1], [0, 1, 0, 0]);
      }

      if (this.__axis[2] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__axis[2], [0, 0, 1, 0]);
      }

      if (this.__rotation[0] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[0], [1, 0, 0, 0]);
      }

      if (this.__rotation[1] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[1], [0, 1, 0, 0]);
      }

      if (this.__rotation[2] !== 0) {
        this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].rotate(this.__model, this.__rotation[2], [0, 0, 1, 0]);
      }

      this.__model = _matrix_js__WEBPACK_IMPORTED_MODULE_1__["default"].scale(this.__model, this.__scale);

      this.__objects.forEach(function (object, name) {
        // console.log(object);
        object.render(application, _this.__model, level);
      });

      this.__children.forEach(function (reference, name) {
        reference.render(application, _this.__model, level);
      });
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "objects",
    get: function get() {
      return this.__objects;
    }
  }, {
    key: "children",
    get: function get() {
      return this.__children;
    }
  }]);

  return Reference;
}();



/***/ }),

/***/ "./src/js/x/graphics/shader.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/shader.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Shader; });
/* harmony import */ var _core_command_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../core/command.js */ "./src/js/x/core/command.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Shader = /*#__PURE__*/function () {
  _createClass(Shader, null, [{
    key: "load",
    value: function load(path, name, category, type, application) {
      return new _core_command_js__WEBPACK_IMPORTED_MODULE_0__["default"](function (resolve, reject) {
        var w = new Worker('/xgraphics/js/homeworld2/shader.load.js');
        w.postMessage({
          path: path
        });

        w.onmessage = function (event) {
          if (event.data.finish) {
            if (!event.data.error) {
              var shader = application.shader(new Shader(name, category, type, event.data.code));
              application.__current += Shader.weight;
              resolve(shader);
            } else {
              reject(e);
            }

            w.terminate();
            w = null;
          }
        };
      }, Shader.weight);
    }
  }, {
    key: "type",
    value: function type(gl, category, _type) {
      switch (category) {
        case Shader.vertex:
          return gl.VERTEX_SHADER;

        case Shader.fragment:
          return gl.FRAGMENT_SHADER;

        case Shader.compute:
          throw new Error();

        case Shader.geometry:
          throw new Error();

        case Shader.tessellation:
          throw new Error();

        default:
          throw new Error();
      }
    }
  }, {
    key: "weight",
    get: function get() {
      return 1;
    }
  }, {
    key: "none",
    get: function get() {
      return 0;
    }
  }, {
    key: "vertex",
    get: function get() {
      return 1;
    }
  }, {
    key: "fragment",
    get: function get() {
      return 2;
    }
  }, {
    key: "compute",
    get: function get() {
      return 3;
    }
  }, {
    key: "geometry",
    get: function get() {
      return 4;
    }
  }, {
    key: "tessellation",
    get: function get() {
      return 5;
    }
  }, {
    key: "control",
    get: function get() {
      return 1;
    }
  }, {
    key: "evaluation",
    get: function get() {
      return 2;
    }
  }]);

  function Shader(name, category, type, code) {
    _classCallCheck(this, Shader);

    this.__name = name;
    this.__category = category;
    this.__type = type || Shader.none;
    this.__id = 0;
    this.__code = code;
  }

  _createClass(Shader, [{
    key: "load",
    value: function load(application) {
      var gl = application.gl;

      if (!this.__id) {
        this.__id = gl.createShader(Shader.type(gl, this.__category, this.__type));
        gl.shaderSource(this.__id, this.__code);
        gl.compileShader(this.__id);

        if (!gl.getShaderParameter(this.__id, gl.COMPILE_STATUS)) {
          console.log(gl.getShaderInfoLog(this.__id));
          throw new Error();
        }

        return this;
      } else {
        throw new Error();
      }
    }
  }, {
    key: "unload",
    value: function unload(application) {
      var gl = application.gl;

      if (this.__id) {
        gl.deleteShader(this.__id);
        this.__id = 0;
      }
    }
  }, {
    key: "name",
    get: function get() {
      return this.__name;
    }
  }, {
    key: "id",
    get: function get() {
      return this.__id;
    }
  }]);

  return Shader;
}();



/***/ }),

/***/ "./src/js/x/graphics/surface.js":
/*!**************************************!*\
  !*** ./src/js/x/graphics/surface.js ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Surface; });
/* harmony import */ var _light_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./light.js */ "./src/js/x/graphics/light.js");
/* harmony import */ var _camera_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./camera.js */ "./src/js/x/graphics/camera.js");
/* harmony import */ var _projection_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./projection.js */ "./src/js/x/graphics/projection.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }





var Surface = /*#__PURE__*/function () {
  function Surface(canvas) {
    _classCallCheck(this, Surface);

    this.__canvas = canvas;
    this.__context = null;
    this.__background = [0, 0, 0, 1];
    this.__references = new Map();
    this.__light = new _light_js__WEBPACK_IMPORTED_MODULE_0__["default"]([18, 7, 30, 1], [1, 1, 1, 1], 0.8);
    this.__camera = new _camera_js__WEBPACK_IMPORTED_MODULE_1__["default"]([0, 0, 90, 1], [0, 0, 0, 0], [0, 1, 0, 0]);
    this.__projection = new _projection_js__WEBPACK_IMPORTED_MODULE_2__["default"](45, 1, 0.1, 1000.0);
    this.__extension = null;
    this.__canvas.style.backgroundColor = "black"; // background-color : black;
  }

  _createClass(Surface, [{
    key: "initialize",
    value: function initialize() {
      if (!this.__context) {
        this.__context = this.__canvas.getContext("webgl") || this.__canvas.getContext("experimental-webgl");

        var extension = this.__context.getExtension('OES_vertex_array_object') || this.__context.getExtension('MOZ_OES_vertex_array_object') || this.__context.getExtension('WEBKIT_OES_vertex_array_object');

        this.__extension = {
          extension: extension
        };

        this.__context.viewport(0, 0, this.__canvas.width, this.__canvas.height);

        this.__context.enable(this.__context.DEPTH_TEST);

        this.__context.depthFunc(this.__context.LESS);

        this.__context.enable(this.__context.BLEND);

        this.__context.blendFunc(this.__context.SRC_ALPHA, this.__context.ONE_MINUS_SRC_ALPHA);
      }
    }
  }, {
    key: "gl",
    get: function get() {
      return this.__context;
    }
  }, {
    key: "extension",
    get: function get() {
      return this.__extension;
    }
  }, {
    key: "background",
    get: function get() {
      return this.__background;
    }
  }, {
    key: "width",
    get: function get() {
      return this.__canvas.width;
    }
  }, {
    key: "height",
    get: function get() {
      return this.__canvas.height;
    }
  }, {
    key: "light",
    get: function get() {
      return this.__light;
    }
  }, {
    key: "camera",
    get: function get() {
      return this.__camera;
    }
  }, {
    key: "projection",
    get: function get() {
      return this.__projection;
    }
  }]);

  return Surface;
}();



/***/ }),

/***/ "./src/js/x/graphics/texture.js":
/*!**************************************!*\
  !*** ./src/js/x/graphics/texture.js ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Texture; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

/**
 * 현재 COMPRESSED_RGBA_S3TC_DXT5_EXT 만 지원합니다.
 * gl.generateMipmap(gl.TEXTURE_2D); 에서 예외가 발생합니다.
 *
 */
var Texture = /*#__PURE__*/function () {
  _createClass(Texture, null, [{
    key: "getTarget",
    value: function getTarget(extension, format) {
      switch (format) {
        case 1146639413:
          return extension.COMPRESSED_RGBA_S3TC_DXT5_EXT;

        default:
          throw new Error();
      }
    }
  }]);

  function Texture(name, format) {
    _classCallCheck(this, Texture);

    this.__name = name;
    this.__format = format;
    this.__id = null;
    this.__mipmaps = [];
  }

  _createClass(Texture, [{
    key: "push",
    value: function push(o) {
      this.__mipmaps.push(o);
    }
  }, {
    key: "load",
    value: function load(application) {
      var gl = application.gl;
      var extension = application.extension;
      var ext = gl.getExtension('WEBGL_compressed_texture_s3tc') || gl.getExtension('MOZ_WEBGL_compressed_texture_s3tc') || gl.getExtension('WEBKIT_WEBGL_compressed_texture_s3tc');

      if (!this.__id) {
        this.__id = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, this.__id);

        this.__mipmaps.forEach(function (mipmap, index) {
          gl.compressedTexImage2D(gl.TEXTURE_2D, index, ext.COMPRESSED_RGBA_S3TC_DXT5_EXT, mipmap.width, mipmap.height, 0, mipmap.data);
        });

        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR); // gl.generateMipmap(gl.TEXTURE_2D);
      }
    }
  }, {
    key: "unload",
    value: function unload(application) {
      var gl = application.gl;
    }
  }, {
    key: "id",
    get: function get() {
      return this.__id;
    }
  }]);

  return Texture;
}();



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



/***/ }),

/***/ "./src/js/x/graphics/vertex.js":
/*!*************************************!*\
  !*** ./src/js/x/graphics/vertex.js ***!
  \*************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Vertex; });
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }

var Vertex = /*#__PURE__*/function () {
  _createClass(Vertex, null, [{
    key: "stride",
    get: function get() {
      return 88;
    }
  }]);

  function Vertex(location, normal, color) {
    _classCallCheck(this, Vertex);

    this.location = location || [0, 0, 0, 1];
    this.normal = normal || [0, 0, 0, 0];
    this.color = color || [0, 0, 0, 1];
    this.texture = [0, 0];
    this.tangent = [0, 0, 0, 0];
    this.binormal = [0, 0, 0, 0];
  }

  return Vertex;
}();



/***/ }),

/***/ "./src/js/x/graphics/vertices.js":
/*!***************************************!*\
  !*** ./src/js/x/graphics/vertices.js ***!
  \***************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "default", function() { return Vertices; });
/* harmony import */ var _vector_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./vector.js */ "./src/js/x/graphics/vector.js");
function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } }

function _createClass(Constructor, protoProps, staticProps) { if (protoProps) _defineProperties(Constructor.prototype, protoProps); if (staticProps) _defineProperties(Constructor, staticProps); return Constructor; }



var Vertices = /*#__PURE__*/function () {
  _createClass(Vertices, null, [{
    key: "modeFromStr",
    value: function modeFromStr(s) {
      if (s === "triangle") {
        return Vertices.triangle;
      } else {
        throw new Error();
      }

      return s;
    }
  }, {
    key: "none",
    get: function get() {
      return 0;
    }
  }, {
    key: "point",
    get: function get() {
      return 1;
    }
  }, {
    key: "line",
    get: function get() {
      return 2;
    }
  }, {
    key: "patch",
    get: function get() {
      return 3;
    }
  }, {
    key: "triangle",
    get: function get() {
      return 4;
    }
  }, {
    key: "strip",
    get: function get() {
      return 1;
    }
  }, {
    key: "loop",
    get: function get() {
      return 2;
    }
  }, {
    key: "fan",
    get: function get() {
      return 3;
    }
  }, {
    key: "adjacent",
    get: function get() {
      return 1;
    }
  }]);

  function Vertices() {
    _classCallCheck(this, Vertices);

    this.__mode = Vertices.none;
    this.__type = Vertices.none;
    this.__adjacency = Vertices.none;
    this.__id = Vertices.none;
    this.__vertices = [];
  }

  _createClass(Vertices, [{
    key: "each",
    value: function each(f) {
      this.__vertices.forEach(f);
    }
  }, {
    key: "push",
    value: function push(v) {
      this.__vertices.push(v);
    }
  }, {
    key: "set",
    value: function set(v) {
      this.__vertices = v;
    }
  }, {
    key: "load",
    value: function load(application) {
      // console.log("vertices load");
      var gl = application.gl;
    }
  }, {
    key: "unload",
    value: function unload(application) {
      console.log("vertices unload");
      var gl = application.gl;
    }
  }, {
    key: "bind",
    value: function bind(application) {
      console.log("vertices bind");
      var gl = application.gl;
    }
  }, {
    key: "serialize",
    value: function serialize(buffer) {
      console.log("serialize");
      var array = [];
      var total = 0;

      this.__vertices.forEach(function (vertex) {
        var result = [];
        array.push(new Float32Array(result.concat(_vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(vertex.location, 1.0), _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(vertex.normal, 0.0), _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(vertex.color, 1.0), _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].two(vertex.texture), _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(vertex.tangent, 0.0), _vector_js__WEBPACK_IMPORTED_MODULE_0__["default"].four(vertex.binormal, 0.0))));
        total += array[array.length - 1].length;
      });

      var o = new Float32Array(total);
      total = 0;
      array.forEach(function (value) {
        o.set(value, total);
        total += value.length;
      });
      buffer.data = o;
    }
  }, {
    key: "size",
    get: function get() {
      return this.__vertices.length;
    }
  }, {
    key: "mode",
    set: function set(v) {
      this.__mode = v;
    }
  }]);

  return Vertices;
}();



/***/ })

/******/ });
//# sourceMappingURL=bundle.js.map