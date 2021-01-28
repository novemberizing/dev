import React from 'react';
import Strings from '../../../util/strings';
import Breakpoint from '../../breakpoint';
import Context from '../../context';

export default class InputGroup extends Context {
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }

    static size(prefix, type, suffix = "") {
        if(prefix) {
            switch(type) {
                case InputGroup.sm: return Breakpoint.name(prefix, type, suffix);
                case InputGroup.lg: return Breakpoint.name(prefix, type, suffix);
            }
        }
        return undefined;
    }
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            nowrap,
            size,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "input-group",
            nowrap && "flex-nowrap",
            InputGroup.size("input-group", size)
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "input-group")
        };

        return (
            <Context.Provider value={context}>
                <div className={classNames} {...props}>{children}</div>
            </Context.Provider>
        );
    }
}