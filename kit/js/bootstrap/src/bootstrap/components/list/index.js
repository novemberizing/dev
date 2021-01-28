import React from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Breakpoint from '../../breakpoint';

export default class List extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            flush,
            horizontal,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "list-group",
            flush && "list-group-flush",
            horizontal && (Breakpoint.name('list-group-horizontal', horizontal) || 'list-group-horizontal')
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "list-group")
        };

        return (
            <Context.Provider value={context}>
                <ul className={classNames} {...props}>{children}</ul>
            </Context.Provider>
        );
    }
}