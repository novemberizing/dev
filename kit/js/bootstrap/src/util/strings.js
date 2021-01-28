/**
 * UTIL: STRING
 */

export default class Strings {
    /**
     * 
     * @param {Array/String} array      | 
     * @param {String}       separator 
     */
    static join(o, separator = ' ') {
        if(o instanceof Array) {
            return o.filter(item => item)
                    .map(item => {
                        if(item instanceof Array) {
                            return Strings.join(item, separator);
                        }
                        return item;
                    })
                    .join(separator);
        }
        return o;
    }

    static find(o, item) {
        if(o instanceof Array) {
            return o.find(value => {
                if(item instanceof Array) {
                    return item.find(child => child === value);
                }
                return item === value;
            });
        }
        if(item instanceof Array) {
            return item.find(value => o === value);
        }
        return o === item;
    }
}