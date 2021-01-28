import React, { Component } from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Contextual from '../../contextual';

export default class Carousel extends Context {
    constructor(props) {
        super(props);

        this.node = null;

        this.onSlide = this.onSlide.bind(this);
        this.onSlid = this.onSlid.bind(this);
    }

    cycle() {

    }

    pause() {

    }

    prev() {

    }

    next() {

    }

    nextWhenVisible() {

    }

    to() {

    }

    onSlide(event) {
        if(this.props.onSlide) {
            this.props.onSlide(event);
        }
    }

    onSlid(event) {
        if(this.props.onSlide) {
            this.props.onSlid(event);
        }
    }

    componentDidMount() {
        this.node.addEventListener('slide.bs.carousel', this.onSlide);
        this.node.addEventListener('slid.bs.carousel', this.onSlid);
    }

    componentWillUnmount() {
        this.node.removeEventListener('slide.bs.carousel', this.onSlide);
        this.node.removeEventListener('slid.bs.carousel', this.onSlid);
    }

    render() {
        const { 
            className,
            id,
            children,
            fade,
            dark,
            onSlide,
            onSlid,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "carousel",
            "slide",
            fade && 'carousel-fade',
            dark && 'carousel-dark'
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "carousel")
        };

        return (
            <Context.Provider value={context}>
                <div ref={node=> this.node = node} id={id} className={classNames} data-bs-ride="carousel" {...props}>
                    {children}
                </div>
            </Context.Provider>

        );
    }
}