/**
 * BOOTSTRAP COMPONENT: ITEM
 * 
 */
import React from 'react';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

import Context from './context';

export default class Item extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            Collections.last(this.context.type) === "accordion" && "accordion-item"
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<div className={classNames} {...props}>{children}</div>)
    }
}