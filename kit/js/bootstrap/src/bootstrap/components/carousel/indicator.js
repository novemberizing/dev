import React from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';

export default class CarouselIndicator extends Context {
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
            "carousel-indicators"
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "carousel-indicators")
        };

        return (
            <Context.Provider value={context}>
                <ol className={classNames} {...props}>{children}</ol>
            </Context.Provider>
        );
    }
}