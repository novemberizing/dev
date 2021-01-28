/**
 * 
 */
import React from 'react';

import Context from '../context';

import Strings from '../../util/strings';
import Collections from '../../util/collections';
import Breakpoint from '../breakpoint';

export default class Select extends Context {
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }

    static size(prefix, type, suffix = null) {
        if(prefix) {
            switch(type){
                case Select.sm: return Breakpoint.name(prefix, type, suffix);
                case Select.lg: return Breakpoint.name(prefix, type, suffix);
            }
        }
        return null;
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
            multiple,
            ...additional
        } = this.props;

        const form = Collections.find(this.context.type, "form");

        const classNames = Strings.join([
            className,
            form && ["form-select", Select.size('form-select', size)],
        ]);

        const props = Object.assign(additional,
            multiple ? { multiple: {}, size: multiple } : undefined
        );

        return (
            <select className={classNames} aria-label={label} {...props}>
                {children}
            </select>
        );
    }
}