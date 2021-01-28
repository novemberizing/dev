/**
 * BOOTSTRAP COMPONENT: HYPERLINK
 */

import React from 'react';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

import Context from '../context';
import Contextual from '../contextual';
import Button from './button';
import ListItem from './list/item';

export default class Hyperlink extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            role,
            href,
            children,
            contextual,
            size,
            disabled,
            active,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            (role === 'button' && parent !== 'carousel') && ['btn', Contextual.name('btn', contextual)], disabled && 'disabled', size && Button.size('btn', size),
            (role !== 'button' && parent === 'card') && 'card-link',
            Collections.find(this.context.type, "alert") && 'alert-link',
            parent === 'dropdown' && 'dropdown-item',
            parent === 'list-group' && Strings.join(['list-group-item list-group-item-action', Contextual.name('list-group-item', contextual)]),
            parent === 'page' && 'page-link',
            Collections.find(parent, ['nav', 'tab']) && 'nav-link',
            active && 'active'
        ]);

        const props = Object.assign(additional,
            disabled ? { tabIndex: -1, 'aria-disabled': true } : undefined,
            active ? { 'aria-current': true } : undefined,
            Collections.find(Collections.last(this.context.type), ['nav', 'tab'])  && active ? { 'aria-current': 'page' } : undefined
        );

        const last = Collections.last(this.context.type);

        const listitem = Collections.find(Collections.last(this.context.type), ["nav", "tab", "dropdown", "page"]);

        const listItemClassName = Strings.join([
            parent === 'page' && disabled && "disabled",
            parent === 'page' && active && "active"
        ]);

        return listitem ? (<ListItem className={listItemClassName}><a href={href || '#'} className={classNames} role={role} {...props}>{children}</a></ListItem>)
                        : (<a href={href || '#'} className={classNames} role={role} {...props}>{children}</a>);
    }
}