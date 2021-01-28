/**
 * 
 * 
 */

import React from 'react';

import Context from '../../context';
import Contextual from '../../contextual';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

export default class ListItem extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            active,
            disabled,
            contextual,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            active && 'active',
            disabled && 'disabled',
            Contextual.name('list-group-item', contextual),
            parent === "page" && "page-item",
            parent === "nav" && 'nav-item',
            parent === "list-group" && "list-group-item"
        ]);

        const props = Object.assign(additional,
            disabled ? { 'aria-disabled': true } : undefined,
            active ? { 'aria-current': true } : undefined
        );

        const context = this.context;

        return (
            <Context.Provider value={context}>
                <li className={classNames} {...props}>{children}</li>
            </Context.Provider>
        );
    }
}