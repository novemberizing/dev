/**
 * 
 */

import React from 'react';

import Context from '../../context';
import Contextual from '../../contextual';

import Strings from '../../../util/strings';

export default class Toast extends Context {
    constructor(props) {
        super(props);

        this.node = null;

        this.onShow = this.onShow.bind(this);
        this.onShown = this.onShown.bind(this);
        this.onHide = this.onHide.bind(this);
        this.onHidden = this.onHidden.bind(this);
    }

    show() {

    }

    hide() {

    }

    componentDidMount() {
        this.node.addEventListener('show.bs.toast', this.onShow);
        this.node.addEventListener('shown.bs.toast', this.onShown);
        this.node.addEventListener('hide.bs.toast', this.onHide);
        this.node.addEventListener('hidden.bs.toast', this.onHidden);
    }

    componentWillUnmount() {
        this.node.removeEventListener('show.bs.toast', this.onShow);
        this.node.removeEventListener('shown.bs.toast', this.onShown);
        this.node.removeEventListener('hide.bs.toast', this.onHide);
        this.node.removeEventListener('hidden.bs.toast', this.onHidden);
    }

    onShow(event) {
        if(this.props.onShow) {
            this.props.onShow(event);
        }
    }

    onShown(event) {
        if(this.props.onShown) {
            this.props.onShown(event);
        }
    }

    onHide(event) {
        if(this.props.onHide) {
            this.props.onHide(event);
        }
    }

    onHidden(event) {
        if(this.props.onHidden) {
            this.props.onHidden(event);
        }
    }

    render() {
        const {
            onShow,
            onShown,
            onHide,
            onHidden,
            className,
            children,
            color,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "toast",
            Contextual.name('bg', color)
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, 'toast')
        };

        return (
            <Context.Provider value={context}>
                <div ref={node => this.node = node} className={classNames}
                    role="alert"
                    aria-live="assertive"
                    aria-atomic="true"
                    {...props}>
                    {children}
                </div>
            </Context.Provider>
        );
    }
}