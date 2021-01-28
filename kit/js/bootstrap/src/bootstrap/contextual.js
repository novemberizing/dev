import Strings from "../util/strings";

export default class Contextual {
    static name(prefix, type, suffix, separator = "-") {
        switch(type) {
            case Contextual.primary:   return Strings.join([prefix, type, suffix], separator);
            case Contextual.secondary: return Strings.join([prefix, type, suffix], separator);
            case Contextual.success:   return Strings.join([prefix, type, suffix], separator);
            case Contextual.danger:    return Strings.join([prefix, type, suffix], separator);
            case Contextual.warning:   return Strings.join([prefix, type, suffix], separator);
            case Contextual.info:      return Strings.join([prefix, type, suffix], separator);
            case Contextual.light:     return Strings.join([prefix, type, suffix], separator);
            case Contextual.dark:      return Strings.join([prefix, type, suffix], separator);
        }
        return undefined;
    }

    static get primary() { return "primary"; }
    static get secondary() { return "secondary"; }
    static get success() { return "success"; }
    static get danger() { return "danger"; }
    static get warning() { return "warning"; }
    static get info() { return "info"; }
    static get light() { return "light"; }
    static get dark() { return "dark"; }
}