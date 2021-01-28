/**
 * BOOTSTRAP COMPONENT - PARAGRAPH
 */

import React, { Component } from 'react';
import Collections from '../../util/collections';

import Strings from '../../util/strings';
import Context from '../context';

export default class Paragraph extends Context {
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
            Collections.last(this.context.type) === 'card' && 'card-text'
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<p className={classNames} {...props}>{children}</p>)
    }
}