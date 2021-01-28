/**
 * UTILITY: COLLECTION
 */

export default class Collections {
    static exist(collection) {
        if(collection instanceof Array) {
            return collection.length > 0;
        }
        return collection;
    }
    static filter(collection, func) {
        if(collection instanceof Array) {
            return collection.filter(func);
        }
        return func(collection, 0, [collection]) ? [collection] : null;
    }

    static map(collection, func) {
        if(collection instanceof Array) {
            return collection.filter(item => item)
                             .map(func);
        }
        return func(collection, 0, [collection]);
    }

    static push(collection, item) {
        if(collection instanceof Array) {
            if(item instanceof Array) {
                return collection.concat(item);
            }
            collection.push(item);
            return collection;
        }
        return item instanceof Array ? item : [item];
    }

    static last(collection) {
        if(collection instanceof Array) {
            return collection[collection.length - 1];
        }
        return collection;
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