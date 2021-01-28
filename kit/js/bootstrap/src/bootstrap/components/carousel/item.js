import React, { Component } from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

export default class CarouselInner extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const { 
            className,
            children,
            active,
            src,
            alt,
            interval,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "carousel-item",
            active && 'active'
        ]);

        const props = Object.assign(additional,
            interval ? { 'data-bs-interval': interval } : undefined
        );

        return (
            <div className={classNames} {...props}>
                <img src={src} alt={alt} className={className} />
                {Collections.exist(children) && <div className="carousel-caption d-none d-md-block">{children}</div>}
            </div>
        );
    }
}