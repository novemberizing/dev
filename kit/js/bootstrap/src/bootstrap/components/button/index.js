/**
 * 
 */
import React from 'react';

import Strings from '../../../util/strings';
import Contextual from '../../contextual';

import Context from '../../context';
import Collections from '../../../util/collections';

export default class Button extends Context {
    static get sm(){ return 'sm'; }
    static get lg(){ return 'lg'; }

    static size(prefix, type, suffix, separator = '-') {
        switch(type) {
            case Button.sm: return Strings.join([prefix, type, suffix], separator);
            case Button.lg: return Strings.join([prefix, type, suffix], separator);
        }
        return undefined;
    }

    constructor(props) {
        super(props);
    }

    toggle() {
        // IMPLEMENT THIS
    }

    render() {
        const {
            className,
            children,
            contextual,
            outline,
            type,
            size,
            toggle,
            target,
            active,
            dismiss,
            white,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            parent !== "toast" && "btn",
            Contextual.name(outline ? 'btn-outline' : 'btn', contextual),
            Button.size('btn', size),
            type === 'link' && 'btn-link',
            active && 'active',
            type === 'close' && 'btn-close',
            type === 'close' && white && 'btn-close-white',
            parent === 'list-group' && 'list-group-item list-group-item-action',
            className
        ]);

        const props = Object.assign(additional,
            target ? { 'data-bs-target': target } : undefined,
            toggle === 'modal' ? { 'data-bs-toggle': 'modal' } : undefined,
            toggle === true ? { 'data-bs-toggle': 'button', autoComplete: 'off' } : undefined,
            toggle && active ? { 'aria-pressed': true } : undefined,
            type==='close' ? { 'aria-label': 'Close' } : undefined,
            (parent === 'list-group' && active) ? { 'aria-current': true } : undefined,
            parent === 'modal' && dismiss ? { 'data-bs-dismiss': 'modal' } : undefined
        );

        return (<button type={type==='close' ? 'button' : type || 'button'} className={classNames} {...props}>{children}</button>)
    }
}