
export default class Bootstraps {
    static className(category, type, value = null) {
        if(category && type) {
            return category + '-' + type;
        }
        return value;
    }

    static lg(category, size) {
        if(category && size) {
            return category + '-lg-' + size;
        }
        return null;
    }

    static xl(category, size) {
        if(category && size) {
            return category + '-xl-' + size;
        }
        return null;
    }

    static md(category, size) {
        if(category && size) {
            return category + '-md-' + size;
        }
        return null;
    }

    static py(v, value = 'py-3'){
        if(v) {
            return `py-${v}`;
        }
        return value;
    }

    static height(v, value = 'h-100') {
        if(v) {
            return `h-${v}`;
        }
        return value;
    }

    static mb(v, value = "mb-4") {
        if(v) {
            return `mb-${v}`;
        }
        return value;
    }
}