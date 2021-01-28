/**
 * 
 */
import React, { Component } from 'react';

import Strings from '../../../util/strings';

import Contextual from '../../contextual';

export default class ProgressBar extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            min,
            max,
            now,
            striped,
            contextual,
            animated,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "progress-bar",
            Contextual.name('bg', contextual),
            striped && "progress-bar-striped",
            animated && "progress-bar-animated"
        ]);

        const total = (max || 100) - (min || 0);
        const percent = ((now || 0) / total) * 100;

        const props = Object.assign(additional,
            percent ? { style: { width: `${percent}%`}} : undefined
        );

        return (
            <div className={classNames}
                 role="progressbar"
                 aria-valuemin={min || 0}
                 aria-valuemax={max ? max : 100}
                 aria-valuenow={now || 0}
                 {...props}>
                {children}
            </div>);
        
    }
}