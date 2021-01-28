/**
 * 
 */
import React from 'react';
import Strings from '../../util/strings';
import Breakpoint from '../breakpoint';

import Context from '../context';

export default class Pagination extends Context {
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }

    static size(type) {
        switch(type){
            case Pagination.sm: return Breakpoint.name('pagination', type);
            case Pagination.lg: return Breakpoint.name('pagination', type);
        }
        return undefined;
    }

    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            size,
            label,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "pagination",
            Pagination.size(size)
        ]);

        const props = Object.assign(additional,
            label ? { 'aria-label': label } : undefined
        );

        const context = {
            type: Context.push(this.context.type, "page")
        };

        return (
            <Context.Provider value={context}>
                <nav {...props}>
                    <ul className={classNames}>
                        {children}
                    </ul>
                </nav>
            </Context.Provider>
        );
    }
}