static const char CONTENT_HOME_JS[] PROGMEM = 
  "\"use strict\";function OpenEVSEError(e){var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\";this.type=e,this.message=t}function OpenEVSERequest(){var t=this;t._done=function(){},t._error=function(){},t._always=function(){},t.done=function(e){return t._done=e,t},t.error=function(e){return t._error=e,t},t.always=function(e){return t._always=e,t}}function OpenEVSE(e){var l=this;l._version=\"0.1\",l._endpoint=e,l.states={0:\"unknown\",1:\"not connected\",2:\"connected\",3:\"charging\",4:\"vent required\",5:\"diode check failed\",6:\"gfci fault\",7:\"no ground\",8:\"stuck relay\",9:\"gfci self-test failure\",10:\"over temperature\",254:\"sleeping\",255:\"disabled\"},l._lcd_colors=[\"off\",\"red\",\"green\",\"yellow\",\"blue\",\"violet\",\"teal\",\"white\"],l._status_functions={disable:\"FD\",enable:\"FE\",sleep:\"FS\"},l._lcd_types=[\"monochrome\",\"rgb\"],l._service_levels=[\"A\",\"1\",\"2\"],l.STANDARD_SERIAL_TIMEOUT=.5,l.RESET_SERIAL_TIMEOUT=10,l.STATUS_SERIAL_TIMEOUT=0,l.SYNC_SERIAL_TIMEOUT=.5,l.NEWLINE_MAX_AGE=5,l.CORRECT_RESPONSE_PREFIXES=\"$NK\",l.regex=/\\$([^^]*)(\\^..)?/,l._request=function(e){var a=1<arguments.length&&void 0!==arguments[1]?arguments[1]:function(){},t=\"$\"+(Array.isArray(e)?e.join(\"+\"):e),r=new OpenEVSERequest;return $.get(l._endpoint+\"?json=1&rapi=\"+encodeURI(t),function(e){var t=e.ret.match(l.regex);if(null!==t){var n=t[1].split(\" \");\"OK\"===n[0]?(a(n.slice(1)),r._done(n.slice(1))):r._error(new OpenEVSEError(\"OperationFailed\"))}else r._error(new OpenEVSEError(\"UnexpectedResponse\"))},\"json\").always(function(){r._always()}).fail(function(){r._error(new OpenEVSEError(\"RequestFailed\"))}),r},l._flags=function(n){var a=l._request(\"GE\",function(e){var t=parseInt(e[1],16);isNaN(t)?a._error(new OpenEVSEError(\"ParseError\",'Failed to parse \"'+e[0]+'\"')):n({service_level:1+(1&t),diode_check:0==(2&t),vent_required:0==(4&t),ground_check:0==(8&t),stuck_relay_check:0==(16&t),auto_service_level:0==(32&t),auto_start:0==(64&t),serial_debug:0!=(128&t),lcd_type:0!=(256&t)?\"monochrome\":\"rgb\",gfi_self_test:0==(512&t),temp_check:0==(1024&t)})});return a},l.reset=function(){return l._request(\"FR\")},l.time=function(u){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S1\",e.getFullYear()-2e3,e.getMonth()+1,e.getDate(),e.getHours(),e.getMinutes(),e.getSeconds()],function(){l.time(u)});var c=l._request(\"GT\",function(e){if(6<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]),a=parseInt(e[2]),r=parseInt(e[3]),o=parseInt(e[4]),i=parseInt(e[5]);if(isNaN(t)||isNaN(n)||isNaN(a)||isNaN(r)||isNaN(o)||isNaN(i))c._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments'));else if(165==t&&165==n&&165==a&&165==r&&165==o&&85==i)u(new Date(0),!1);else{var s=new Date(2e3+t,n-1,a,r,o,i);u(s,!0)}}else c._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return c},l.timer=function(o){var i=1<arguments.length&&void 0!==arguments[1]&&arguments[1],s=2<arguments.length&&void 0!==arguments[2]&&arguments[2];function u(e){return(e<10?\"0\":\"\")+e}if(!1!==i&&!1!==s){var e=/([01]\\d|2[0-3]):([0-5]\\d)/,t=i.match(e),n=s.match(e);return null!==t&&null!==n?l._request([\"ST\",parseInt(t[1]),parseInt(t[2]),parseInt(n[1]),parseInt(n[2])],function(){l.timer(o)}):!1}var c=l._request(\"GD\",function(e){if(4<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]),a=parseInt(e[2]),r=parseInt(e[3]);isNaN(t)||isNaN(n)||isNaN(a)||isNaN(r)?c._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments')):0===t&&0===n&&0===a&&0===r?o(!1,\"--:--\",\"--:--\"):(i=u(t)+\":\"+u(n),s=u(a)+\":\"+u(r),o(!0,i,s))}else c._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return c},l.cancelTimer=function(e){return l._request([\"ST\",0,0,0,0],function(){e()})},l.time_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S3\",Math.round(e/15)],function(){l.time_limit(n)});var a=l._request(\"G3\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?a._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(15*t)}else a._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return a},l.charge_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SH\",e],function(){l.charge_limit(n)});var a=l._request(\"GH\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?a._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)}else a._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return a},l.ammeter_settings=function(a){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SA\",e,t],function(){a(e,t)});var r=l._request(\"GA\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):a(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.current_capacity=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SC\",e],function(){l.current_capacity(n)});var a=l._request(\"GE\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?a._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)}else a._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return a},l.service_level=function(t){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];return!1!==e?l._request([\"SL\",l._service_levels[e]],function(){l.service_level(t)}):l._flags(function(e){t(e.auto_service_level?0:e.service_level,e.service_level)})},l.current_capacity_range=function(a){var r=l._request(\"GC\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):a(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.status=function(a){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e){var t=l._status_functions[e];return l._request([t],function(){l.status(a)})}var r=l._request(\"GS\",function(e){if(1<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):a(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.diode_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF\",\"D\",e?\"1\":\"0\"],function(){l.diode_check(t)}):l._flags(function(e){t(e.diode_check)})},l.gfi_self_test=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF F\",e?\"1\":\"0\"],function(){l.gfi_self_test(t)}):l._flags(function(e){t(e.gfi_self_test)})},l.ground_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF G\",e?\"1\":\"0\"],function(){l.ground_check(t)}):l._flags(function(e){t(e.ground_check)})},l.stuck_relay_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF R\",e?\"1\":\"0\"],function(){l.stuck_relay_check(t)}):l._flags(function(e){t(e.stuck_relay_check)})},l.vent_required=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF V\",e?\"1\":\"0\"],function(){l.vent_required(t)}):l._flags(function(e){t(e.vent_required)})},l.temp_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF T\",e?\"1\":\"0\"],function(){l.temp_check(t)}):l._flags(function(e){t(e.temp_check)})},l.over_temperature_thresholds=function(a){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SO\",e,t],function(){l.over_temperature_thresholds(a)});var r=l._request(\"GO\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):a(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.press_button=function(e){return l._request(\"F1\",function(){e()})},l.setEndpoint=function(e){l._endpoint=e}}function RapiViewModel(e){var t=this;t.baseEndpoint=e,t.rapiSend=ko.observable(!1),t.cmd=ko.observable(\"\"),t.ret=ko.observable(\"\"),t.send=function(){t.rapiSend(!0),$.get(t.baseEndpoint()+\"/r?json=1&rapi=\"+encodeURI(t.cmd()),function(e){t.ret(\">\"+e.ret),t.cmd(e.cmd)},\"json\").always(function(){t.rapiSend(!1)})}}function TimeViewModel(n){var a=this;function r(e){return(e<10?\"0\":\"\")+e}a.evseTimedate=ko.observable(new Date),a.localTimedate=ko.observable(new Date),a.nowTimedate=ko.observable(null),a.hasRTC=ko.observable(!0),a.elapsedNow=ko.observable(new Date(0)),a.elapsedLocal=ko.observable(new Date),a.divertUpdateNow=ko.observable(new Date(0)),a.divertUpdateLocal=ko.observable(new Date),a.date=ko.pureComputed({read:function(){if(null===a.nowTimedate())return\"\";var e=a.nowTimedate();return e.getFullYear()+\"-\"+r(e.getMonth()+1)+\"-\"+r(e.getDate())},write:function(e){a.evseTimedate(new Date(e)),a.localTimedate(new Date)}}),a.time=ko.pureComputed({read:function(){if(null===a.nowTimedate())return\"--:--:--\";var e=a.nowTimedate();return r(e.getHours())+\":\"+r(e.getMinutes())+\":\"+r(e.getSeconds())},write:function(e){var t=e.split(\":\"),n=a.evseTimedate();n.setHours(parseInt(t[0])),n.setMinutes(parseInt(t[1])),a.evseTimedate(n),a.localTimedate(new Date)}}),a.elapsed=ko.pureComputed(function(){if(null===a.nowTimedate())return\"0:00:00\";var e=a.elapsedNow().getTime(),t=(e=Math.floor(e/1e3))%60,n=(e=Math.floor(e/60))%60;return Math.floor(e/60)+\":\"+r(n)+\":\"+r(t)}),n.status.elapsed.subscribe(function(e){a.elapsedNow(new Date(1e3*e)),a.elapsedLocal(new Date)}),a.divert_update=ko.pureComputed(function(){if(null===a.nowTimedate())return!1;var e=a.divertUpdateNow().getTime();return Math.floor(e/1e3)}),n.status.divert_update.subscribe(function(e){a.divertUpdateNow(new Date(1e3*e)),a.divertUpdateLocal(new Date)});var o=null;a.automaticTime=ko.observable(!0),a.setTime=function(){var e=a.automaticTime()?new Date:a.evseTimedate();n.openevse.time(a.timeUpdate,e)},a.timeUpdate=function(e){var t=!(1<arguments.length&&void 0!==arguments[1])||arguments[1];a.hasRTC(t),null!==o&&(clearInterval(o),o=null),a.evseTimedate(e),a.nowTimedate(e),a.localTimedate(new Date),o=setInterval(function(){a.automaticTime()&&a.nowTimedate(new Date(a.evseTimedate().getTime()+(new Date-a.localTimedate()))),n.isCharging()&&a.elapsedNow(new Date(1e3*n.status.elapsed()+(new Date-a.elapsedLocal()))),a.divertUpdateNow(new Date(1e3*n.status.divert_update()+(new Date-a.divertUpdateLocal())))},1e3)}}function OpenEvseViewModel(e,t){var r=this,n=ko.pureComputed(function(){return e()+\"/r\"});r.openevse=new OpenEVSE(n()),n.subscribe(function(e){r.openevse.setEndpoint(e)}),r.status=t,r.time=new TimeViewModel(r),r.serviceLevels=[{name:\"Auto\",value:0},{name:\"1\",value:1},{name:\"2\",value:2}],r.currentLevels=ko.observableArray([]),r.timeLimits=[{name:\"none\",value:0},{name:\"15 min\",value:15},{name:\"30 min\",value:30},{name:\"45 min\",value:45},{name:\"1 hour\",value:60},{name:\"1.5 hours\",value:90},{name:\"2 hours\",value:120},{name:\"2.5 hours\",value:150},{name:\"3 hours\",value:180},{name:\"4 hours\",value:240},{name:\"5 hours\",value:300},{name:\"6 hours\",value:360},{name:\"7 hours\",value:420},{name:\"8 hours\",value:480}],r.chargeLimits=[{name:\"none\",value:0},{name:\"1 kWh\",value:1},{name:\"2 kWh\",value:2},{name:\"3 kWh\",value:3},{name:\"4 kWh\",value:4},{name:\"5 kWh\",value:5},{name:\"6 kWh\",value:6},{name:\"7 kWh\",value:7},{name:\"8 kWh\",value:8},{name:\"9 kWh\",value:9},{name:\"10 kWh\",value:10},{name:\"15 kWh\",value:11},{name:\"20 kWh\",value:12},{name:\"25 kWh\",value:25},{name:\"30 kWh\",value:30},{name:\"35 kWh\",value:35},{name:\"40 kWh\",value:40},{name:\"45 kWh\",value:45},{name:\"50 kWh\",value:50},{name:\"55 kWh\",value:55},{name:\"60 kWh\",value:60},{name:\"70 kWh\",value:70},{name:\"80 kWh\",value:80},{name:\"90 kWh\",value:90}],r.serviceLevel=ko.observable(-1),r.actualServiceLevel=ko.observable(-1),r.minCurrentLevel=ko.observable(-1),r.maxCurrentLevel=ko.observable(-1),r.currentCapacity=ko.observable(-1),r.timeLimit=ko.observable(-1),r.chargeLimit=ko.observable(-1),r.delayTimerEnabled=ko.observable(!1),r.delayTimerStart=ko.observable(\"--:--\"),r.delayTimerStop=ko.observable(\"--:--\"),r.gfiSelfTestEnabled=ko.observable(!1),r.groundCheckEnabled=ko.observable(!1),r.stuckRelayEnabled=ko.observable(!1),r.tempCheckEnabled=ko.observable(!1),r.diodeCheckEnabled=ko.observable(!1),r.ventRequiredEnabled=ko.observable(!1),r.allTestsEnabled=ko.pureComputed(function(){return r.gfiSelfTestEnabled()&&r.groundCheckEnabled()&&r.stuckRelayEnabled()&&r.tempCheckEnabled()&&r.diodeCheckEnabled()&&r.ventRequiredEnabled()}),r.tempCheckSupported=ko.observable(!1),r.isConnected=ko.pureComputed(function(){return-1!==[2,3].indexOf(r.status.state())}),r.isReady=ko.pureComputed(function(){return-1!==[0,1].indexOf(r.status.state())}),r.isCharging=ko.pureComputed(function(){return 3===r.status.state()}),r.isError=ko.pureComputed(function(){return-1!==[4,5,6,7,8,9,10].indexOf(r.status.state())}),r.isEnabled=ko.pureComputed(function(){return-1!==[0,1,2,3].indexOf(r.status.state())}),r.isSleeping=ko.pureComputed(function(){return 254===r.status.state()}),r.isDisabled=ko.pureComputed(function(){return 255===r.status.state()}),r.selectTimeLimit=function(e){if(r.timeLimit()!==e)for(var t=0;t<r.timeLimits.length;t++){var n=r.timeLimits[t];if(n.value>=e){r.timeLimit(n.value);break}}},r.selectChargeLimit=function(e){if(r.chargeLimit()!==e)for(var t=0;t<r.chargeLimits.length;t++){var n=r.chargeLimits[t];if(n.value>=e){r.chargeLimit(n.value);break}}};var a=[function(){return r.openevse.time(r.time.timeUpdate)},function(){return r.openevse.service_level(function(e,t){r.serviceLevel(e),r.actualServiceLevel(t)})},function(){return r.updateCurrentCapacity()},function(){return r.openevse.current_capacity(function(e){r.currentCapacity(e)})},function(){return r.openevse.time_limit(function(e){r.selectTimeLimit(e)})},function(){return r.openevse.charge_limit(function(e){r.selectChargeLimit(e)})},function(){return r.openevse.gfi_self_test(function(e){r.gfiSelfTestEnabled(e)})},function(){return r.openevse.ground_check(function(e){r.groundCheckEnabled(e)})},function(){return r.openevse.stuck_relay_check(function(e){r.stuckRelayEnabled(e)})},function(){return r.openevse.temp_check(function(e){r.tempCheckEnabled(e)})},function(){return r.openevse.diode_check(function(e){r.diodeCheckEnabled(e)})},function(){return r.openevse.vent_required(function(e){r.ventRequiredEnabled(e)})},function(){return r.openevse.temp_check(function(){r.tempCheckSupported(!0)},r.tempCheckEnabled()).error(function(){r.tempCheckSupported(!1)})},function(){return r.openevse.timer(function(e,t,n){r.delayTimerEnabled(e),r.delayTimerStart(t),r.delayTimerStop(n)})}];r.updateCount=ko.observable(0),r.updateTotal=ko.observable(a.length),r.updateCurrentCapacity=function(){return r.openevse.current_capacity_range(function(e,t){r.minCurrentLevel(e),r.maxCurrentLevel(t);var n=r.currentCapacity();r.currentLevels.removeAll();for(var a=r.minCurrentLevel();a<=r.maxCurrentLevel();a++)r.currentLevels.push({name:a+\" A\",value:a});r.currentCapacity(n)})},r.updatingServiceLevel=ko.observable(!1),r.savedServiceLevel=ko.observable(!1),r.updatingCurrentCapacity=ko.observable(!1),r.savedCurrentCapacity=ko.observable(!1),r.updatingTimeLimit=ko.observable(!1),r.savedTimeLimit=ko.observable(!1),r.updatingChargeLimit=ko.observable(!1),r.savedChargeLimit=ko.observable(!1),r.updatingDelayTimer=ko.observable(!1),r.savedDelayTimer=ko.observable(!1),r.updatingStatus=ko.observable(!1),r.savedStatus=ko.observable(!1),r.updatingGfiSelfTestEnabled=ko.observable(!1),r.savedGfiSelfTestEnabled=ko.observable(!1),r.updatingGroundCheckEnabled=ko.observable(!1),r.savedGroundCheckEnabled=ko.observable(!1),r.updatingStuckRelayEnabled=ko.observable(!1),r.savedStuckRelayEnabled=ko.observable(!1),r.updatingTempCheckEnabled=ko.observable(!1),r.savedTempCheckEnabled=ko.observable(!1),r.updatingDiodeCheckEnabled=ko.observable(!1),r.savedDiodeCheckEnabled=ko.observable(!1),r.updatingVentRequiredEnabled=ko.observable(!1),r.savedVentRequiredEnabled=ko.observable(!1);var o=!(r.setForTime=function(e,t){e(!0),setTimeout(function(){e(!1)},t)});function i(e){return/([01]\\d|2[0-3]):([0-5]\\d)/.test(e)}r.subscribe=function(){o||(r.serviceLevel.subscribe(function(e){r.updatingServiceLevel(!0),r.openevse.service_level(function(e,t){r.setForTime(r.savedServiceLevel,2e3),r.actualServiceLevel(t),r.updateCurrentCapacity().always(function(){})},e).always(function(){r.updatingServiceLevel(!1)})}),r.currentCapacity.subscribe(function(t){!0!==r.updatingServiceLevel()&&(r.updatingCurrentCapacity(!0),r.openevse.current_capacity(function(e){r.setForTime(r.savedCurrentCapacity,2e3),t!==e&&r.currentCapacity(e)},t).always(function(){r.updatingCurrentCapacity(!1)}))}),r.timeLimit.subscribe(function(t){r.updatingTimeLimit(!0),r.openevse.time_limit(function(e){r.setForTime(r.savedTimeLimit,2e3),t!==e&&r.selectTimeLimit(e)},t).always(function(){r.updatingTimeLimit(!1)})}),r.chargeLimit.subscribe(function(t){r.updatingChargeLimit(!0),r.openevse.charge_limit(function(e){r.setForTime(r.savedChargeLimit,2e3),t!==e&&r.selectChargeLimit(e)},t).always(function(){r.updatingChargeLimit(!1)})}),r.gfiSelfTestEnabled.subscribe(function(t){r.updatingGfiSelfTestEnabled(!0),r.openevse.gfi_self_test(function(e){r.setForTime(r.savedGfiSelfTestEnabled,2e3),t!==e&&r.gfiSelfTestEnabled(e)},t).always(function(){r.updatingGfiSelfTestEnabled(!1)})}),r.groundCheckEnabled.subscribe(function(t){r.updatingGroundCheckEnabled(!0),r.openevse.ground_check(function(e){r.setForTime(r.savedGroundCheckEnabled,2e3),t!==e&&r.groundCheckEnabled(e)},t).always(function(){r.updatingGroundCheckEnabled(!1)})}),r.stuckRelayEnabled.subscribe(function(t){r.updatingStuckRelayEnabled(!0),r.savedStuckRelayEnabled(!1),r.openevse.stuck_relay_check(function(e){r.savedStuckRelayEnabled(!0),setTimeout(function(){r.savedStuckRelayEnabled(!1)},2e3),t!==e&&r.stuckRelayEnabled(e)},t).always(function(){r.updatingStuckRelayEnabled(!1)})}),r.tempCheckEnabled.subscribe(function(t){r.updatingTempCheckEnabled(!0),r.openevse.temp_check(function(e){r.setForTime(r.savedTempCheckEnabled,2e3),t!==e&&r.tempCheckEnabled(e)},t).always(function(){r.updatingTempCheckEnabled(!1)})}),r.diodeCheckEnabled.subscribe(function(t){r.updatingDiodeCheckEnabled(!0),r.openevse.diode_check(function(e){r.setForTime(r.savedDiodeCheckEnabled,2e3),t!==e&&r.diodeCheckEnabled(e)},t).always(function(){r.updatingDiodeCheckEnabled(!1)})}),r.ventRequiredEnabled.subscribe(function(t){r.updatingVentRequiredEnabled(!0),r.openevse.vent_required(function(e){r.setForTime(r.savedVentRequiredEnabled,2e3),t!==e&&r.ventRequiredEnabled(e)},t).always(function(){r.updatingVentRequiredEnabled(!1)})}),o=!0)},r.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};r.updateCount(0),r.nextUpdate(e)},r.nextUpdate=function(e){(0,a[r.updateCount()])().always(function(){r.updateCount(r.updateCount()+1),r.updateCount()<a.length?r.nextUpdate(e):(r.subscribe(),e())})},r.delayTimerValid=ko.pureComputed(function(){return i(r.delayTimerStart())&&i(r.delayTimerStop())}),r.startDelayTimer=function(){r.updatingDelayTimer(!0),r.openevse.timer(function(){r.delayTimerEnabled(!0)},r.delayTimerStart(),r.delayTimerStop()).always(function(){r.updatingDelayTimer(!1)})},r.stopDelayTimer=function(){r.updatingDelayTimer(!0),r.openevse.cancelTimer(function(){r.delayTimerEnabled(!1)}).always(function(){r.updatingDelayTimer(!1)})},r.setStatus=function(e){var t=r.status.state();\"disabled\"===e&&255===t||\"sleep\"===e&&254===t||\"enable\"===e&&t<254||(r.updatingStatus(!0),!r.delayTimerEnabled()||\"sleep\"!==e&&\"enable\"!==e?r.openevse.status(function(e){r.status.state(e)},e).always(function(){r.updatingStatus(!1)}):r.openevse.press_button(function(){e=!1}).always(function(){r.openevse.status(function(e){r.status.state(e)},e).always(function(){r.updatingStatus(!1)})}))},r.restartFetching=ko.observable(!1),r.restart=function(){confirm(\"Restart OpenEVSE? Current config will be saved, takes approximately 10s.\")&&(r.restartFetching(!0),r.openevse.reset().always(function(){r.restartFetching(!1)}))}}function OpenEvseWiFiViewModel(e,t,n){var a=this;a.baseHost=ko.observable(\"\"!==e?e:\"openevse.local\"),a.basePort=ko.observable(t),a.baseProtocol=ko.observable(n),a.baseEndpoint=ko.pureComputed(function(){var e=\"//\"+a.baseHost();return 80!==a.basePort()&&(e+=\":\"+a.basePort()),e}),a.wsEndpoint=ko.pureComputed(function(){var e=\"ws://\"+a.baseHost();return\"https:\"===a.baseProtocol()&&(e=\"wss://\"+a.baseHost()),80!==a.basePort()&&(e+=\":\"+a.basePort()),e+=\"/ws\"}),a.config=new ConfigViewModel(a.baseEndpoint),a.status=new StatusViewModel(a.baseEndpoint),a.rapi=new RapiViewModel(a.baseEndpoint),a.scan=new WiFiScanViewModel(a.baseEndpoint),a.wifi=new WiFiConfigViewModel(a.baseEndpoint,a.config,a.status,a.scan),a.openevse=new OpenEvseViewModel(a.baseEndpoint,a.status),a.initialised=ko.observable(!1),a.updating=ko.observable(!1),a.scanUpdating=ko.observable(!1),a.bssid=ko.observable(\"\"),a.bssid.subscribe(function(e){for(var t=0;t<a.scan.results().length;t++){var n=a.scan.results()[t];if(e===n.bssid())return void a.config.ssid(n.ssid())}}),a.showMqttInfo=ko.observable(!1),a.showSolarDivert=ko.observable(!1),a.showSafety=ko.observable(!1),a.toggle=function(e){e(!e())},a.advancedMode=ko.observable(!1),a.advancedMode.subscribe(function(e){a.setCookie(\"advancedMode\",e.toString())}),a.developerMode=ko.observable(!1),a.developerMode.subscribe(function(e){a.setCookie(\"developerMode\",e.toString()),e&&a.advancedMode(!0)});var r=null,o=null,i=\"status\";\"\"!==window.location.hash&&(i=window.location.hash.substr(1)),a.tab=ko.observable(i),a.tab.subscribe(function(e){window.location.hash=\"#\"+e}),a.isSystem=ko.pureComputed(function(){return\"system\"===a.tab()}),a.isServices=ko.pureComputed(function(){return\"services\"===a.tab()}),a.isStatus=ko.pureComputed(function(){return\"status\"===a.tab()}),a.isRapi=ko.pureComputed(function(){return\"rapi\"===a.tab()}),a.upgradeUrl=ko.observable(\"about:blank\"),a.loadedCount=ko.observable(0),a.itemsLoaded=ko.pureComputed(function(){return a.loadedCount()+a.openevse.updateCount()}),a.itemsTotal=ko.observable(2+a.openevse.updateTotal()),a.start=function(){a.updating(!0),a.status.update(function(){a.loadedCount(a.loadedCount()+1),a.config.update(function(){a.loadedCount(a.loadedCount()+1),a.baseHost().endsWith(\".local\")&&\"\"!==a.status.ipaddress()&&(\"\"===a.config.www_username()?a.baseHost(a.status.ipaddress()):window.location.replace(\"http://\"+a.status.ipaddress()+\":\"+a.basePort())),a.openevse.update(function(){a.initialised(!0),r=setTimeout(a.update,5e3),a.upgradeUrl(a.baseEndpoint()+\"/update\");for(var e=document.getElementsByTagName(\"img\"),t=0;t<e.length;t++)e[t].getAttribute(\"data-src\")&&e[t].setAttribute(\"src\",e[t].getAttribute(\"data-src\"));a.updating(!1)})}),a.connect()}),a.advancedMode(\"true\"===a.getCookie(\"advancedMode\",\"false\")),a.developerMode(\"true\"===a.getCookie(\"developerMode\",\"false\"))};var s=!(a.update=function(){a.updating()||(a.updating(!0),null!==r&&(clearTimeout(r),r=null),a.status.update(function(){r=setTimeout(a.update,5e3),a.updating(!1)}))});a.startScan=function(){a.scanUpdating()||(s=!0,a.scanUpdating(!0),null!==o&&(clearTimeout(o),o=null),a.scan.update(function(){s&&(o=setTimeout(a.startScan,3e3)),a.scanUpdating(!1)}))},a.stopScan=function(){s=!1,a.scanUpdating()||null!==o&&(clearTimeout(o),o=null)},a.wifiConnecting=ko.observable(!1),a.status.mode.subscribe(function(e){\"STA+AP\"!==e&&\"STA\"!==e||a.wifiConnecting(!1),\"STA+AP\"===e||\"AP\"===e?a.startScan():a.stopScan()}),a.saveNetworkFetching=ko.observable(!1),a.saveNetworkSuccess=ko.observable(!1),a.saveNetwork=function(){\"\"===a.config.ssid()?alert(\"Please select network\"):(a.saveNetworkFetching(!0),a.saveNetworkSuccess(!1),$.post(a.baseEndpoint()+\"/savenetwork\",{ssid:a.config.ssid(),pass:a.config.pass()},function(){a.saveNetworkSuccess(!0),a.wifiConnecting(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){a.saveNetworkFetching(!1)}))},a.saveAdminFetching=ko.observable(!1),a.saveAdminSuccess=ko.observable(!1),a.saveAdmin=function(){a.saveAdminFetching(!0),a.saveAdminSuccess(!1),$.post(a.baseEndpoint()+\"/saveadmin\",{user:a.config.www_username(),pass:a.config.www_password()},function(){a.saveAdminSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){a.saveAdminFetching(!1)})},a.saveAdvancedFetching=ko.observable(!1),a.saveAdvancedSuccess=ko.observable(!1),a.saveAdvanced=function(){a.saveAdvancedFetching(!0),a.saveAdvancedSuccess(!1),$.post(a.baseEndpoint()+\"/saveadvanced\",{hostname:a.config.hostname()},function(){a.saveAdvancedSuccess(!0),confirm(\"These changes require a reboot to take effect. Reboot now?\")&&$.post(a.baseEndpoint()+\"/restart\",{},function(){setTimeout(function(){var e=\"http://\"+a.config.hostname()+\".local\";80!=a.basePort()&&(e+=\":\"+a.basePort()),e+=\"/\",window.location.replace(e)},5e3)}).fail(function(){alert(\"Failed to restart\")})}).fail(function(){alert(\"Failed to save Advanced config\")}).always(function(){a.saveAdvancedFetching(!1)})},a.saveEmonCmsFetching=ko.observable(!1),a.saveEmonCmsSuccess=ko.observable(!1),a.saveEmonCms=function(){var e={enable:a.config.emoncms_enabled(),server:a.config.emoncms_server(),apikey:a.config.emoncms_apikey(),node:a.config.emoncms_node(),fingerprint:a.config.emoncms_fingerprint()};!e.enable||\"\"!==e.server&&\"\"!==e.node?e.enable&&32!==e.apikey.length&&\"___DUMMY_PASSWORD___\"!==e.apikey?alert(\"Please enter valid Emoncms apikey\"):e.enable&&\"\"!==e.fingerprint&&59!==e.fingerprint.length?alert(\"Please enter valid SSL SHA-1 fingerprint\"):(a.saveEmonCmsFetching(!0),a.saveEmonCmsSuccess(!1),$.post(a.baseEndpoint()+\"/saveemoncms\",e,function(){a.saveEmonCmsSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){a.saveEmonCmsFetching(!1)})):alert(\"Please enter Emoncms server and node\")},a.saveMqttFetching=ko.observable(!1),a.saveMqttSuccess=ko.observable(!1),a.saveMqtt=function(){var e={enable:a.config.mqtt_enabled(),protocol:a.config.mqtt_protocol(),server:a.config.mqtt_server(),port:a.config.mqtt_port(),reject_unauthorized:a.config.mqtt_reject_unauthorized(),topic:a.config.mqtt_topic(),user:a.config.mqtt_user(),pass:a.config.mqtt_pass(),solar:a.config.mqtt_solar(),grid_ie:a.config.mqtt_grid_ie()};e.enable&&\"\"===e.server?alert(\"Please enter MQTT server\"):(a.saveMqttFetching(!0),a.saveMqttSuccess(!1),$.post(a.baseEndpoint()+\"/savemqtt\",e,function(){a.saveMqttSuccess(!0)}).fail(function(){alert(\"Failed to save MQTT config\")}).always(function(){a.saveMqttFetching(!1)}))},a.saveOhmKeyFetching=ko.observable(!1),a.saveOhmKeySuccess=ko.observable(!1),a.saveOhmKey=function(){a.saveOhmKeyFetching(!0),a.saveOhmKeySuccess(!1),$.post(a.baseEndpoint()+\"/saveohmkey\",{enable:a.config.ohm_enabled(),ohm:a.config.ohmkey()},function(){a.saveOhmKeySuccess(!0)}).fail(function(){alert(\"Failed to save Ohm key config\")}).always(function(){a.saveOhmKeyFetching(!1)})},a.turnOffAccessPointFetching=ko.observable(!1),a.turnOffAccessPointSuccess=ko.observable(!1),a.turnOffAccessPoint=function(){a.turnOffAccessPointFetching(!0),a.turnOffAccessPointSuccess(!1),$.post(a.baseEndpoint()+\"/apoff\",{},function(e){console.log(e),\"\"!==a.status.ipaddress()?setTimeout(function(){window.location=\"http://\"+a.status.ipaddress(),a.turnOffAccessPointSuccess(!0)},3e3):a.turnOffAccessPointSuccess(!0)}).fail(function(){alert(\"Failed to turn off Access Point\")}).always(function(){a.turnOffAccessPointFetching(!1)})},a.changeDivertModeFetching=ko.observable(!1),a.changeDivertModeSuccess=ko.observable(!1),a.changeDivertMode=function(e){a.status.divertmode()!==e&&(a.status.divertmode(e),a.changeDivertModeFetching(!0),a.changeDivertModeSuccess(!1),$.post(a.baseEndpoint()+\"/divertmode\",{divertmode:e},function(){a.changeDivertModeSuccess(!0)}).fail(function(){alert(\"Failed to set divert mode\")}).always(function(){a.changeDivertModeFetching(!1)}))},a.isEcoModeAvailable=ko.pureComputed(function(){return a.config.mqtt_enabled()&&(\"\"!==a.config.mqtt_solar()||\"\"!==a.config.mqtt_grid_ie())}),a.ecoMode=ko.pureComputed({read:function(){return 2===a.status.divertmode()},write:function(e){a.changeDivertMode(e?2:1)}}),a.haveSolar=ko.pureComputed(function(){return\"\"!==a.config.mqtt_solar()}),a.haveGridIe=ko.pureComputed(function(){return\"\"!==a.config.mqtt_grid_ie()}),a.factoryResetFetching=ko.observable(!1),a.factoryResetSuccess=ko.observable(!1),a.factoryReset=function(){confirm(\"CAUTION: Do you really want to Factory Reset? All setting and config will be lost.\")&&(a.factoryResetFetching(!0),a.factoryResetSuccess(!1),$.post(a.baseEndpoint()+\"/reset\",{},function(){a.factoryResetSuccess(!0)}).fail(function(){alert(\"Failed to Factory Reset\")}).always(function(){a.factoryResetFetching(!1)}))},a.restartFetching=ko.observable(!1),a.restartSuccess=ko.observable(!1),a.restart=function(){confirm(\"Restart OpenEVSE WiFi? Current config will be saved, takes approximately 10s.\")&&(a.restartFetching(!0),a.restartSuccess(!1),$.post(a.baseEndpoint()+\"/restart\",{},function(){a.restartSuccess(!0)}).fail(function(){alert(\"Failed to restart\")}).always(function(){a.restartFetching(!1)}))},a.updateFetching=ko.observable(!1),a.updateComplete=ko.observable(!1),a.updateError=ko.observable(\"\"),a.updateFilename=ko.observable(\"\"),a.updateLoaded=ko.observable(0),a.updateTotal=ko.observable(1),a.updateProgress=ko.pureComputed(function(){return a.updateLoaded()/a.updateTotal()*100}),a.otaUpdate=function(){if(\"\"!==a.updateFilename()){a.updateFetching(!0),a.updateError(\"\");var e=$(\"#upload_form\")[0],t=new FormData(e);$.ajax({url:\"/update\",type:\"POST\",data:t,contentType:!1,processData:!1,xhr:function(){var e=new window.XMLHttpRequest;return e.upload.addEventListener(\"progress\",function(e){e.lengthComputable&&(a.updateLoaded(e.loaded),a.updateTotal(e.total))},!1),e}}).done(function(e){console.log(e),\"OK\"==e?a.updateComplete(!0):a.updateError(e)}).fail(function(){a.updateError(\"HTTP Update failed\")}).always(function(){a.updateFetching(!1)})}else a.updateError(\"Filename not set\")},a.pingInterval=!1,a.reconnectInterval=!1,a.socket=!1,a.connect=function(){a.socket=new WebSocket(a.wsEndpoint()),a.socket.onopen=function(e){console.log(e),a.pingInterval=setInterval(function(){a.socket.send('{\"ping\":1}')},1e3)},a.socket.onclose=function(e){console.log(e),a.reconnect()},a.socket.onmessage=function(e){console.log(e),ko.mapping.fromJSON(e.data,a.status)},a.socket.onerror=function(e){console.log(e),a.socket.close(),a.reconnect()}},a.reconnect=function(){!1!==a.pingInterval&&(clearInterval(a.pingInterval),a.pingInterval=!1),!1===a.reconnectInterval&&(a.reconnectInterval=setTimeout(function(){a.reconnectInterval=!1,a.connect()},500))},a.setCookie=function(e,t){var n=2<arguments.length&&void 0!==arguments[2]&&arguments[2],a=\"\";if(!1!==n){var r=new Date;r.setTime(r.getTime()+24*n*60*60*1e3),a=\";expires=\"+r.toUTCString()}document.cookie=e+\"=\"+t+a+\";path=/\"},a.getCookie=function(e){for(var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\",n=e+\"=\",a=document.cookie.split(\";\"),r=0;r<a.length;r++){for(var o=a[r];\" \"===o.charAt(0);)o=o.substring(1);if(0===o.indexOf(n))return o.substring(n.length,o.length)}return t}}function scaleString(e,t,n){return(parseInt(e)/t).toFixed(n)}function formatUpdate(e){if(!1===e)return\"N/A\";var t=e/60,n=e/3600,a=n/24,r=e.toFixed(0)+\"s\";return 0===e.toFixed(0)?r=\"now\":7<a?r=\"inactive\":2<a?r=a.toFixed(1)+\" days\":2<n?r=n.toFixed(0)+\" hrs\":180<e&&(r=t.toFixed(0)+\" mins\"),r}function updateClass(e){if(!1===e)return\"\";var t=\"updateBad\";return(e=Math.abs(e))<25?t=\"updateGood\":e<60?t=\"updateSlow\":e<7200&&(t=\"updateSlower\"),t}!function(){var t=window.location.hostname,n=window.location.port,a=window.location.protocol;$(function(){var e=new OpenEvseWiFiViewModel(t,n,a);ko.applyBindings(e),e.start()})}();\n"
  "//# sourceMappingURL=home.js.map\n";
