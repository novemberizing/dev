/**
 * 
 */

export default class Strings {
    /**
     * The Strings.join() method creates and returns a new string by concatenating
     * all of the elements in an array (or an array-like object), separated by
     * commas or specified separator string. If the array has only one item,
     * then will be return without using the separator.
     * 
     * @param {Array|String} o parameter
     * @param {String} separator Specifies a string to separate each pair of
     *                           Adjacent elements of the array. The separator
     *                           is converted to a string if necessary. If
     *                           omitted the array elements are separated with
     *                           a comma (","). If separator is an empty string,
     *                           all elements are joined without any characters in
     *                           between them.
     */
    static join(o, separator = ' ') {
        if(o instanceof Array) {
            return o.map(item => {
                if(o instanceof Array) {
                    return Strings.join(item, separator);
                } else if(typeof item === 'string' || item instanceof String) {
                    return item;
                } else if(o) {
                    throw new Error('invalid parameter');
                }
            })
            .filter(o => (o))
            .join(separator);
        } else if(typeof o === 'string' || o instanceof String) {
            return o;
        }  else if(o) {
            throw new Error('invalid parameter');
        }
    }
}