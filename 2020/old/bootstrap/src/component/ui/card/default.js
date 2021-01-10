import React from 'react';
import Bootstraps from '../../../util/bootstraps';
import Reacts from '../../../util/reacts';
import Strings from '../../../util/strings';

export default class DafaultCard extends React.Component {
    render() {
        return (
            <div className={Strings.join(["card", this.props.shadow && "shadow", Bootstraps.mb(this.props.mb)])} >
                {Reacts.display(this.props.title,
                    <div className={Strings.join(["card-header", "font-weight-bold", this.props.type &&Strings.join(['text', this.props.type], '-')])}>
                        {this.props.title}
                    </div>
                )}
                <div className="card-body">
                    {this.props.children}
                </div>
            </div>
        );
    }
}