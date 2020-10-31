
export default class Bootstraps {
    static className(category, type) {
        if(category && type) {
            return category + '-' + type;
        }
        throw new Error();
    }
}