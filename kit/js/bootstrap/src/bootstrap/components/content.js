/**
 * 
 */
import React from 'react';

import Context from '../context';

import Collections from '../../util/collections';
import Strings from '../../util/strings';

export default class Content extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === 'modal' && 'modal-content'
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<div className={classNames} {...props}>{children}</div>);
    }
}