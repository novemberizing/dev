/**
 * 
 */

import React from 'react';
import Strings from '../../../util/strings';
import Collections from '../../../util/collections';
import Context from '../../context';

export default class Navigation extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            pill,
            fill,
            type,
            justified,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === 'navbar' && type !== 'nav' ? 'navbar-nav' : "nav",
            pill && 'nav-pills',
            fill && 'nav-fill',
            justified && 'nav-justified'
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "nav")
        };

        return (
            <Context.Provider value={context}>
                <ul className={classNames} {...props}>{children}</ul>
            </Context.Provider>
        );
    }
}