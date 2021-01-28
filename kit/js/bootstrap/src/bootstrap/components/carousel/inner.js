import React, { Component } from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';

export default class CarouselInner extends Context {
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
            "carousel-inner"
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            <div className={classNames}{...props}>
                {children}
            </div>
        );
    }
}