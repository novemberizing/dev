
export default class Bootstraps {
    static className(category, type, value = null) {
        if(category && type) {
            return category + '-' + type;
        }
        return value;
    }
}