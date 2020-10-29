import React from 'react';
import Alert from './component/alert';

export default class Root extends React.Component {
    render() {
        return (
            <div>
                <Alert type="primary">
                    PRIMARY
                    <a href="#">hello world</a>
                </Alert>
                <Alert type="secondary">SECONDARY</Alert>
                <Alert type="success">SUCCESS</Alert>
                <Alert type="danger">DANGER</Alert>
                <Alert type="warning">WARNING</Alert>
                <Alert type="info">INFO</Alert>
                <Alert type="light">LIGHT</Alert>
                <Alert type="dark">DARK</Alert>
            </div>
        );
    }
}