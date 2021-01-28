/**
 * BOOTSTRAP COMPONENT: ALERT
 */

import React from 'react';

import Context from '../context';
import Contextual from '../contextual';

import Strings from '../../util/strings';

export default class Alert extends Context {
    constructor(props) {
        super(props);

        this.node = null;

        this.onClose = this.onClose.bind(this);
        this.onClosed = this.onClosed.bind(this);
    }

    close() {

    }

    componentDidMount() {
        this.node.addEventListener('close.bs.alert', this.onClose);
        this.node.addEventListener('closed.bs.alert', this.onClosed);
    }

    componentWillUnmount() {
        this.node.removeEventListener('close.bs.alert', this.onClose);
        this.node.removeEventListener('closed.bs.alert', this.onClosed);
    }

    onClose(event) {
        console.log("alert", "onClose", event);
        if(this.props.onClosed) {
            this.props.onClose(event);
        }
    }

    onClosed(event) {
        console.log("alert", "onClosed", event);
        if(this.props.onClosed) {
            this.props.onClosed(event);
        }
    }

    render() {
        const {
            className,
            contextual,
            dismissible,
            children,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            'alert',
            Contextual.name('alert', contextual),
            dismissible && 'alert-dismissible fade show',
            className
        ]);

        const props = Object.assign(additional,
            dismissible ? {  } : undefined
        );

        const context = {
            type: Context.push(this.context.type, "alert"),
        };

        return (
            <Context.Provider value={context}>
                <div ref={node => this.node = node} className={classNames} {...props} role="alert">
                    {children}
                    {dismissible && <button type="button" className="btn-close" data-bs-dismiss="alert" aria-label="Close" />}
                </div>
            </Context.Provider>
        );
    }
}