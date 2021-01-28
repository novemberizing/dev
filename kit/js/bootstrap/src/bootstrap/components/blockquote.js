/**
 * BOOTSTRAP ELEMENT - BLOCKQUOTE
 */

import React from 'react';

import Context from '../context';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

export default class Blockquote extends Context {
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
            "blockquote",
            className
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "blockquote"),
        };

        return (
            <Context.Provider value={context}>
                <blockquote className={classNames} {...props}>{children}</blockquote>
            </Context.Provider>
        )
    }
}