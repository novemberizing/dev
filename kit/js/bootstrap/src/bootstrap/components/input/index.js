/**
 * 
 */

import React from 'react';
import Strings from '../../../util/strings';
import Collections from '../../../util/collections';
import Context from '../../context';
import Contextual from '../../contextual';
import ListItem from '../list/item';
import Breakpoint from '../../breakpoint';

export default class Input extends Context {
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }

    static size(prefix, type) {
        if(prefix) {
            switch(type) {
                case Input.sm: return Breakpoint.name(prefix, type);
                case Input.lg: return Breakpoint.name(prefix, type);
            }
        }
        return undefined;
    }

    constructor(props) {
        super(props);
    }

    render() {
        const {
            type,
            className,
            contextual,
            value,
            size,
            label,
            children,
            plaintext,
            invalid,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const control = (additional.readOnly && plaintext) ? "form-control-plaintext" : "form-control";

        const classNames = Strings.join([
            Strings.find(type, ["button", "submit", "reset"]) && ['btn', Contextual.name('btn', contextual)],
            type!=='checkbox' && Collections.find(this.context.type, "form") && [control, Input.size(control, size)],
            className,
            type==='checkbox' && 'form-check-input',
            type==='color' && 'form-control-color',
            invalid && 'is-invalid'
            
        ]);

        const props = Object.assign(additional,
            label ? { 'aria-label': label } : undefined
        );

        return (parent === 'list-group' ? <ListItem key={0}><input key={1} type={type} className={classNames} {...props} value={value} /> {children}</ListItem>
                                        : [<input key={2} type={type} className={classNames} {...props} value={value} />, children]);
    }
}