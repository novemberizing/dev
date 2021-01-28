/**
 * 
 */
import React from 'react';
import Strings from '../../../util/strings';

import Context from '../../context';

export default class ButtonGroup extends Context {
    static get sm(){ return 'sm'; }
    static get lg(){ return 'lg'; }

    static size(prefix, type, suffix, separator = '-') {
        switch(type) {
            case ButtonGroup.sm: return Strings.join([prefix, type, suffix], separator);
            case ButtonGroup.lg: return Strings.join([prefix, type, suffix], separator);
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
            label,
            size,
            vertical,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            vertical ? "btn-group-vertical" : "btn-group",
            ButtonGroup.size("btn-group", size)
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "btn-group")
        };

        return (
            <Context.Provider value={context}>
                <div className={classNames} role="group" aria-label={label} {...props}>
                    {children}
                </div>
            </Context.Provider>
        );
    }
}