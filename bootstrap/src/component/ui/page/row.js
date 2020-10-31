import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Card from '../card';
import DashboardCard from '../card/dashboard';
import DashboardProgressCard from '../card/dashboard/progress';

export default class PageRow extends React.Component {
    render() {
        return (
            <div className="row">
                {this.props.children}
            </div>
        );
    }
}