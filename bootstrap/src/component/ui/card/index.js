import React from 'react';
import Bootstraps from '../../../util/bootstraps';
import Strings from '../../../util/strings';

export default class Card extends React.Component {
    _border(border, type) {
        if(border && type) {
            return Bootstraps.className(`card-border-${this.props.border}`, this.props.type);
        }
        return null;
    }

    render() {
        return (
            <div className={Strings.join(["mb-4", Bootstraps.xl("col", this.props.xl), Bootstraps.md("col", this.props.md)])} >
                <div className={Strings.join(["card", "shadow", Bootstraps.height(this.props.height), Bootstraps.py(this.props.py), this._border(this.props.border, this.props.type)])}>
                    <div className="card-body">
                        {this.props.children}
                    </div>
                </div>
            </div>
        );
        
    }
}