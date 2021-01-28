import Strings from "../util/strings";

export default class Breakpoint {
    static name(prefix, type, suffix, separator = '-') {
        switch(type) {
            case Breakpoint.sm: return Strings.join([prefix, type, suffix], separator);
            case Breakpoint.md: return Strings.join([prefix, type, suffix], separator);
            case Breakpoint.lg: return Strings.join([prefix, type, suffix], separator);
            case Breakpoint.xl: return Strings.join([prefix, type, suffix], separator);
            case Breakpoint.xxl: return Strings.join([prefix, type, suffix], separator);
        }
        return undefined;
    }
    
    static get xs(){ return ''; }
    static get sm(){ return 'sm'; }
    static get md(){ return 'md'; }
    static get lg(){ return 'lg'; }
    static get xl(){ return 'xl'; }
    static get xxl(){ return 'xxl'; }
}