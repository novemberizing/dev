/**
 * 
 */
import React, { Children } from 'react';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

import Context from '../../context';

export default class Breadcrumb extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            divider,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "breadcrumb",
            className
        ]);

        const props = Object.assign(additional,
            (divider || divider==='') ? {style: { '--bs-breadcrumb-divider': `'${divider}'`}} : undefined
        );

        const context = {
            type: Context.push(this.context.type, "breadcrumb")
        };

        const elements = Collections.map(children, (element, index, list) => React.cloneElement(element, {key: index, index, end: index + 1 === list.length}));

        return (
            <Context.Provider value = {context}>
                <nav className={classNames} {...props}>
                    <ol className="breadcrumb">
                        {elements}
                    </ol>
                </nav>
            </Context.Provider>
        );
    }
}