import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';

import Bootstraps from '../../../../../util/bootstraps';
import Strings from '../../../../../util/strings';

export default class TopbarNavAlarmItem extends React.Component {
    render() {
        return (
            <a className="dropdown-item d-flex align-items-center" href="#">
                <div className="mr-3">
                    <div className={Strings.join(["icon-circle", Bootstraps.className("bg", this.props.type)])}>
                        <FontAwesomeIcon icon={this.props.icon} className="text-white" />
                    </div>
                </div>
                <div>
                    <div className="small text-gray-500">{this.props.date}</div>
                    <span className={this.props.bold ? "font-weight-bold" : ""}>
                        {this.props.message}
                    </span>
                </div>
            </a>
        );
    }
}