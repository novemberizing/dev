/**
 * BOOTSTRAP COMPONENT - FOOTER
 */

import React from 'react';

import Context from '../context';
import Contextual from '../contextual';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

export default class Footer extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            border,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === "blockquote" && "blockquote-footer",
            parent === "card" && "card-footer",
            parent === 'modal' && "modal-footer",
            Contextual.name('border', border)
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<footer className={classNames} {...props}>{children}</footer>)
    }
}