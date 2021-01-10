
export default class Strings {
    static concat(o, s = ' ') {
        if(o instanceof Array) {
            return o.map(item => {
                if(item) {
                    if(item instanceof Array) {
                        return Strings.concat(item);
                    } else if(typeof item === 'string' || item instanceof String) {
                        return item;
                    } else {
                        // TODO: EXCEPTION HANDLING
                        throw new Error();
                    }
                }
            }).join(s);
        }
        return "";
    }
}