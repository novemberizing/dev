/**
 * 
 */
import React from 'react';

import Context from '../context';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

export default class Label extends Context {
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
            Collections.find(this.context.type, "form") && 'form-label'
        ]);

        const props = Object.assign(additional,
            {}
        );
        return (<label className={classNames} {...props}>{children}</label>);
    }
}