import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';

import Context from '../context';

export default class Body extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            overlay,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === 'card' && (overlay ? "card-img-overlay" : "card-body"),
            parent === 'modal' && 'modal-body',
            parent === 'toast' && 'toast-body'
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            <div className={classNames} {...props}>{children}</div>
        );
    }
}