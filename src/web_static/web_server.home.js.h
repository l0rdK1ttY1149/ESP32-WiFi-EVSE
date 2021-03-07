static const char CONTENT_HOME_JS[] PROGMEM = 
  "\"use strict\";function OpenEVSEError(e){var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\";this.type=e,this.message=t}function OpenEVSERequest(){var t=this;t._done=function(){},t._error=function(){},t._always=function(){},t.done=function(e){return t._done=e,t},t.error=function(e){return t._error=e,t},t.always=function(e){return t._always=e,t}}function OpenEVSE(e){var l=this;l._version=\"0.1\",l._endpoint=e,l.states={0:\"unknown\",1:\"not connected\",2:\"connected\",3:\"charging\",4:\"vent required\",5:\"diode check failed\",6:\"gfci fault\",7:\"no ground\",8:\"stuck relay\",9:\"gfci self-test failure\",10:\"over temperature\",11:\"over current\",254:\"sleeping\",255:\"disabled\"},l._lcd_colors=[\"off\",\"red\",\"green\",\"yellow\",\"blue\",\"violet\",\"teal\",\"white\"],l._status_functions={disable:\"FD\",enable:\"FE\",sleep:\"FS\"},l._lcd_types=[\"monochrome\",\"rgb\"],l._service_levels=[\"A\",\"1\",\"2\"],l.STANDARD_SERIAL_TIMEOUT=.5,l.RESET_SERIAL_TIMEOUT=10,l.STATUS_SERIAL_TIMEOUT=0,l.SYNC_SERIAL_TIMEOUT=.5,l.NEWLINE_MAX_AGE=5,l.CORRECT_RESPONSE_PREFIXES=\"$NK\",l.regex=/\\$([^^]*)(\\^..)?/,l._request=function(e){var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:function(){},e=\"$\"+(Array.isArray(e)?e.join(\"+\"):e),n=new OpenEVSERequest;return $.get(l._endpoint+\"?json=1&rapi=\"+encodeURI(e),function(e){e=e.ret.match(l.regex);null!==e?\"OK\"===(e=e[1].split(\" \"))[0]?(t(e.slice(1)),n._done(e.slice(1))):n._error(new OpenEVSEError(\"OperationFailed\")):n._error(new OpenEVSEError(\"UnexpectedResponse\"))},\"json\").always(function(){n._always()}).fail(function(){n._error(new OpenEVSEError(\"RequestFailed\"))}),n},l._flags=function(n){var o=l._request(\"GE\",function(e){var t=parseInt(e[1],16);isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Failed to parse \"'+e[0]+'\"')):n({service_level:1+(1&t),diode_check:0==(2&t),vent_required:0==(4&t),ground_check:0==(8&t),stuck_relay_check:0==(16&t),auto_service_level:0==(32&t),auto_start:0==(64&t),serial_debug:0!=(128&t),lcd_type:0!=(256&t)?\"monochrome\":\"rgb\",gfi_self_test:0==(512&t),temp_check:0==(1024&t)})});return o},l.reset=function(){return l._request(\"FR\")},l.time=function(s){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S1\",e.getFullYear()-2e3,e.getMonth()+1,e.getDate(),e.getHours(),e.getMinutes(),e.getSeconds()],function(){l.time(s)});var u=l._request(\"GT\",function(e){var t,n,o,r,a,i;6<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),o=parseInt(e[2]),r=parseInt(e[3]),a=parseInt(e[4]),i=parseInt(e[5]),isNaN(t)||isNaN(n)||isNaN(o)||isNaN(r)||isNaN(a)||isNaN(i)?u._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments')):165==t&&165==n&&165==o&&165==r&&165==a&&85==i?s(new Date(0),!1):(i=new Date(2e3+t,n-1,o,r,a,i),s(i,!0))):u._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return u},l.timer=function(a){var i=1<arguments.length&&void 0!==arguments[1]&&arguments[1],s=2<arguments.length&&void 0!==arguments[2]&&arguments[2];function u(e){return(e<10?\"0\":\"\")+e}if(!1!==i&&!1!==s){var e=/([01]\\d|2[0-3]):([0-5]\\d)/,t=i.match(e),e=s.match(e);return null!==t&&null!==e?l._request([\"ST\",parseInt(t[1]),parseInt(t[2]),parseInt(e[1]),parseInt(e[2])],function(){l.timer(a)}):!1}var c=l._request(\"GD\",function(e){var t,n,o,r;4<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),o=parseInt(e[2]),r=parseInt(e[3]),isNaN(t)||isNaN(n)||isNaN(o)||isNaN(r)?c._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments')):0===t&&0===n&&0===o&&0===r?a(!1,\"--:--\",\"--:--\"):(i=u(t)+\":\"+u(n),s=u(o)+\":\"+u(r),a(!0,i,s))):c._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return c},l.cancelTimer=function(e){return l._request([\"ST\",0,0,0,0],function(){e()})},l.time_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S3\",Math.round(e/15)],function(){l.time_limit(n)});var o=l._request(\"G3\",function(e){var t;1<=e.length?(t=parseInt(e[0]),isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(15*t)):o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.charge_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SH\",e],function(){l.charge_limit(n)});var o=l._request(\"GH\",function(e){var t;1<=e.length?(t=parseInt(e[0]),isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)):o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.ammeter_settings=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SA\",e,t],function(){o(e,t)});var r=l._request(\"GA\",function(e){var t,n;2<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)):r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.current_capacity=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SC\",e],function(){l.current_capacity(n)});var o=l._request(\"GE\",function(e){var t;1<=e.length?(t=parseInt(e[0]),isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)):o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.service_level=function(t){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];return!1!==e?l._request([\"SL\",l._service_levels[e]],function(){l.service_level(t)}):l._flags(function(e){t(e.auto_service_level?0:e.service_level,e.service_level)})},l.current_capacity_range=function(o){var r=l._request(\"GC\",function(e){var t,n;2<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)):r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.status=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e){e=l._status_functions[e];return l._request([e],function(){l.status(o)})}var r=l._request(\"GS\",function(e){var t,n;1<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)):r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.diode_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF\",\"D\",e?\"1\":\"0\"],function(){l.diode_check(t)}):l._flags(function(e){t(e.diode_check)})},l.gfi_self_test=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF F\",e?\"1\":\"0\"],function(){l.gfi_self_test(t)}):l._flags(function(e){t(e.gfi_self_test)})},l.ground_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF G\",e?\"1\":\"0\"],function(){l.ground_check(t)}):l._flags(function(e){t(e.ground_check)})},l.stuck_relay_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF R\",e?\"1\":\"0\"],function(){l.stuck_relay_check(t)}):l._flags(function(e){t(e.stuck_relay_check)})},l.vent_required=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF V\",e?\"1\":\"0\"],function(){l.vent_required(t)}):l._flags(function(e){t(e.vent_required)})},l.temp_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF T\",e?\"1\":\"0\"],function(){l.temp_check(t)}):l._flags(function(e){t(e.temp_check)})},l.over_temperature_thresholds=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SO\",e,t],function(){l.over_temperature_thresholds(o)});var r=l._request(\"GO\",function(e){var t,n;2<=e.length?(t=parseInt(e[0]),n=parseInt(e[1]),isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)):r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.press_button=function(e){return l._request(\"F1\",function(){e()})},l.setEndpoint=function(e){l._endpoint=e}}function RapiViewModel(e){var t=this;t.baseEndpoint=e,t.rapiSend=ko.observable(!1),t.cmd=ko.observable(\"\"),t.ret=ko.observable(\"\"),t.send=function(){t.rapiSend(!0),$.get(t.baseEndpoint()+\"/r?json=1&rapi=\"+encodeURI(t.cmd()),function(e){t.ret(\">\"+e.ret),t.cmd(e.cmd)},\"json\").always(function(){t.rapiSend(!1)})}}function TimeViewModel(n){var o=this;function r(e){return(e<10?\"0\":\"\")+e}o.evseTimedate=ko.observable(new Date),o.localTimedate=ko.observable(new Date),o.nowTimedate=ko.observable(null),o.hasRTC=ko.observable(!0),o.elapsedNow=ko.observable(new Date(0)),o.elapsedLocal=ko.observable(new Date),o.divertUpdateNow=ko.observable(new Date(0)),o.divertUpdateLocal=ko.observable(new Date),o.date=ko.pureComputed({read:function(){if(null===o.nowTimedate())return\"\";var e=o.nowTimedate();return e.getFullYear()+\"-\"+r(e.getMonth()+1)+\"-\"+r(e.getDate())},write:function(e){var t=o.evseTimedate();e+=\" \"+r(t.getHours())+\":\"+r(t.getMinutes())+\":\"+r(t.getSeconds()),o.evseTimedate(new Date(e)),o.localTimedate(new Date)}}),o.time=ko.pureComputed({read:function(){if(null===o.nowTimedate())return\"--:--:--\";var e=o.nowTimedate();return r(e.getHours())+\":\"+r(e.getMinutes())+\":\"+r(e.getSeconds())},write:function(e){var t=e.split(\":\"),e=o.evseTimedate();e.setHours(parseInt(t[0])),e.setMinutes(parseInt(t[1])),o.evseTimedate(e),o.localTimedate(new Date)}}),o.elapsed=ko.pureComputed(function(){if(null===o.nowTimedate())return\"0:00:00\";var e=o.elapsedNow().getTime(),t=(e=Math.floor(e/1e3))%60,n=(e=Math.floor(e/60))%60;return Math.floor(e/60)+\":\"+r(n)+\":\"+r(t)}),n.status.elapsed.subscribe(function(e){o.elapsedNow(new Date(1e3*e)),o.elapsedLocal(new Date)}),o.divert_update=ko.pureComputed(function(){if(null===o.nowTimedate())return!1;var e=o.divertUpdateNow().getTime();return Math.floor(e/1e3)}),n.status.divert_update.subscribe(function(e){o.divertUpdateNow(new Date(1e3*e)),o.divertUpdateLocal(new Date)});var a=null;o.automaticTime=ko.observable(!0),o.timeUpdate=function(e){var t=!(1<arguments.length&&void 0!==arguments[1])||arguments[1];o.hasRTC(t),null!==a&&(clearInterval(a),a=null),o.evseTimedate(e),o.nowTimedate(e),o.localTimedate(new Date),a=setInterval(function(){o.automaticTime()&&o.nowTimedate(new Date(o.evseTimedate().getTime()+(new Date-o.localTimedate()))),n.isCharging()&&o.elapsedNow(new Date(1e3*n.status.elapsed()+(new Date-o.elapsedLocal()))),o.divertUpdateNow(new Date(1e3*n.status.divert_update()+(new Date-o.divertUpdateLocal())))},1e3)}}function TimeZoneViewModel(e){this.name=ko.observable(e.name),this.value=ko.observable(e.name+\"|\"+e.tz)}function ZonesViewModel(e){var o=this,t=ko.pureComputed(function(){return e()+\"/zones.json\"});o.fetching=ko.observable(!1),o.zones=ko.mapping.fromJS([],{key:function(e){return ko.utils.unwrapObservable(e.name)},create:function(e){return new TimeZoneViewModel(e.data)}}),o.initialValue=function(e){e=e.split(\"|\",2);2==e.length?o.zones.push(new TimeZoneViewModel({name:e[0],tz:e[1]})):o.zones.push(new TimeZoneViewModel({name:\"Default\",tz:e[1]}))},o.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};o.fetching(!0),$.get(t(),function(e){var t,n=[];for(t in e)e.hasOwnProperty(t)&&n.push({name:t,tz:e[t]});ko.mapping.fromJS(n,o.zones)},\"json\").always(function(){o.fetching(!1),e()})}}function DummyRequest(){var t=this;t.always=function(e){return e(),t}}function OpenEvseViewModel(e,t,n){var o=this,r=ko.pureComputed(function(){return e()+\"/r\"});o.openevse=new OpenEVSE(r()),r.subscribe(function(e){o.openevse.setEndpoint(e)}),o.status=n,o.config=t,o.time=new TimeViewModel(o),o.serviceLevels=[{name:\"Auto\",value:0},{name:\"1\",value:1},{name:\"2\",value:2}],o.currentLevels=ko.observableArray([]),o.timeLimits=[{name:\"none\",value:0},{name:\"15 min\",value:15},{name:\"30 min\",value:30},{name:\"45 min\",value:45},{name:\"1 hour\",value:60},{name:\"1.5 hours\",value:90},{name:\"2 hours\",value:120},{name:\"2.5 hours\",value:150},{name:\"3 hours\",value:180},{name:\"4 hours\",value:240},{name:\"5 hours\",value:300},{name:\"6 hours\",value:360},{name:\"7 hours\",value:420},{name:\"8 hours\",value:480}],o.chargeLimits=[{name:\"none\",value:0},{name:\"1 kWh\",value:1},{name:\"2 kWh\",value:2},{name:\"3 kWh\",value:3},{name:\"4 kWh\",value:4},{name:\"5 kWh\",value:5},{name:\"6 kWh\",value:6},{name:\"7 kWh\",value:7},{name:\"8 kWh\",value:8},{name:\"9 kWh\",value:9},{name:\"10 kWh\",value:10},{name:\"15 kWh\",value:11},{name:\"20 kWh\",value:12},{name:\"25 kWh\",value:25},{name:\"30 kWh\",value:30},{name:\"35 kWh\",value:35},{name:\"40 kWh\",value:40},{name:\"45 kWh\",value:45},{name:\"50 kWh\",value:50},{name:\"55 kWh\",value:55},{name:\"60 kWh\",value:60},{name:\"70 kWh\",value:70},{name:\"80 kWh\",value:80},{name:\"90 kWh\",value:90}],o.serviceLevel=ko.observable(-1),o.actualServiceLevel=ko.observable(-1),o.minCurrentLevel=ko.observable(-1),o.maxCurrentLevel=ko.observable(-1),o.currentCapacity=ko.observable(-1),o.timeLimit=ko.observable(-1),o.chargeLimit=ko.observable(-1),o.delayTimerEnabled=ko.observable(!1),o.delayTimerStart=ko.observable(\"--:--\"),o.delayTimerStop=ko.observable(\"--:--\"),o.gfiSelfTestEnabled=ko.observable(!1),o.groundCheckEnabled=ko.observable(!1),o.stuckRelayEnabled=ko.observable(!1),o.tempCheckEnabled=ko.observable(!1),o.diodeCheckEnabled=ko.observable(!1),o.ventRequiredEnabled=ko.observable(!1),o.allTestsEnabled=ko.pureComputed(function(){return o.gfiSelfTestEnabled()&&o.groundCheckEnabled()&&o.stuckRelayEnabled()&&o.tempCheckEnabled()&&o.diodeCheckEnabled()&&o.ventRequiredEnabled()}),o.tempCheckSupported=ko.observable(!1),o.isConnected=ko.pureComputed(function(){return-1!==[2,3].indexOf(o.status.state())}),o.isReady=ko.pureComputed(function(){return-1!==[0,1].indexOf(o.status.state())}),o.isCharging=ko.pureComputed(function(){return 3===o.status.state()}),o.isError=ko.pureComputed(function(){return-1!==[4,5,6,7,8,9,10,11].indexOf(o.status.state())}),o.isEnabled=ko.pureComputed(function(){return-1!==[0,1,2,3].indexOf(o.status.state())}),o.isSleeping=ko.pureComputed(function(){return 254===o.status.state()}),o.isDisabled=ko.pureComputed(function(){return 255===o.status.state()}),o.isPaused=ko.pureComputed(function(){return-1!==[254,255].indexOf(o.status.state())}),o.selectTimeLimit=function(e){if(o.timeLimit()!==e)for(var t=0;t<o.timeLimits.length;t++){var n=o.timeLimits[t];if(n.value>=e){o.timeLimit(n.value);break}}},o.selectChargeLimit=function(e){if(o.chargeLimit()!==e)for(var t=0;t<o.chargeLimits.length;t++){var n=o.chargeLimits[t];if(n.value>=e){o.chargeLimit(n.value);break}}};var a=[function(){return!1===o.status.time()?o.openevse.time(o.time.timeUpdate):new DummyRequest},function(){return o.openevse.service_level(function(e,t){o.serviceLevel(e),o.actualServiceLevel(t)})},function(){return o.updateCurrentCapacity()},function(){return o.openevse.current_capacity(function(e){o.currentCapacity(e)})},function(){return o.openevse.time_limit(function(e){o.selectTimeLimit(e)})},function(){return o.openevse.charge_limit(function(e){o.selectChargeLimit(e)})},function(){return o.openevse.gfi_self_test(function(e){o.gfiSelfTestEnabled(e)})},function(){return o.openevse.ground_check(function(e){o.groundCheckEnabled(e)})},function(){return o.openevse.stuck_relay_check(function(e){o.stuckRelayEnabled(e)})},function(){return o.openevse.temp_check(function(e){o.tempCheckEnabled(e)})},function(){return o.openevse.diode_check(function(e){o.diodeCheckEnabled(e)})},function(){return o.openevse.vent_required(function(e){o.ventRequiredEnabled(e)})},function(){return o.openevse.temp_check(function(){o.tempCheckSupported(!0)},o.tempCheckEnabled()).error(function(){o.tempCheckSupported(!1)})},function(){return o.openevse.timer(function(e,t,n){o.delayTimerEnabled(e),o.delayTimerStart(t),o.delayTimerStop(n)})}];o.updateCount=ko.observable(0),o.updateTotal=ko.observable(a.length),o.updateCurrentCapacity=function(){return o.openevse.current_capacity_range(function(e,t){o.minCurrentLevel(e),o.maxCurrentLevel(t);t=o.currentCapacity();o.currentLevels.removeAll();for(var n=o.minCurrentLevel();n<=o.maxCurrentLevel();n++)o.currentLevels.push({name:n+\" A\",value:n});o.currentCapacity(t)})},o.updatingServiceLevel=ko.observable(!1),o.savedServiceLevel=ko.observable(!1),o.updatingCurrentCapacity=ko.observable(!1),o.savedCurrentCapacity=ko.observable(!1),o.updatingTimeLimit=ko.observable(!1),o.savedTimeLimit=ko.observable(!1),o.updatingChargeLimit=ko.observable(!1),o.savedChargeLimit=ko.observable(!1),o.updatingDelayTimer=ko.observable(!1),o.savedDelayTimer=ko.observable(!1),o.updatingStatus=ko.observable(!1),o.savedStatus=ko.observable(!1),o.updatingGfiSelfTestEnabled=ko.observable(!1),o.savedGfiSelfTestEnabled=ko.observable(!1),o.updatingGroundCheckEnabled=ko.observable(!1),o.savedGroundCheckEnabled=ko.observable(!1),o.updatingStuckRelayEnabled=ko.observable(!1),o.savedStuckRelayEnabled=ko.observable(!1),o.updatingTempCheckEnabled=ko.observable(!1),o.savedTempCheckEnabled=ko.observable(!1),o.updatingDiodeCheckEnabled=ko.observable(!1),o.savedDiodeCheckEnabled=ko.observable(!1),o.updatingVentRequiredEnabled=ko.observable(!1),o.savedVentRequiredEnabled=ko.observable(!1);var i=!(o.setForTime=function(e,t){e(!0),setTimeout(function(){e(!1)},t)});function s(e){return/([01]\\d|2[0-3]):([0-5]\\d)/.test(e)}o.subscribe=function(){i||(o.serviceLevel.subscribe(function(e){o.updatingServiceLevel(!0),o.openevse.service_level(function(e,t){o.setForTime(o.savedServiceLevel,2e3),o.actualServiceLevel(t),o.updateCurrentCapacity().always(function(){})},e).always(function(){o.updatingServiceLevel(!1)})}),o.currentCapacity.subscribe(function(t){!0!==o.updatingServiceLevel()&&(o.updatingCurrentCapacity(!0),o.openevse.current_capacity(function(e){o.setForTime(o.savedCurrentCapacity,2e3),t!==e&&o.currentCapacity(e)},t).always(function(){o.updatingCurrentCapacity(!1)}))}),o.timeLimit.subscribe(function(t){o.updatingTimeLimit(!0),o.openevse.time_limit(function(e){o.setForTime(o.savedTimeLimit,2e3),t!==e&&o.selectTimeLimit(e)},t).always(function(){o.updatingTimeLimit(!1)})}),o.chargeLimit.subscribe(function(t){o.updatingChargeLimit(!0),o.openevse.charge_limit(function(e){o.setForTime(o.savedChargeLimit,2e3),t!==e&&o.selectChargeLimit(e)},t).always(function(){o.updatingChargeLimit(!1)})}),o.gfiSelfTestEnabled.subscribe(function(t){o.updatingGfiSelfTestEnabled(!0),o.openevse.gfi_self_test(function(e){o.setForTime(o.savedGfiSelfTestEnabled,2e3),t!==e&&o.gfiSelfTestEnabled(e)},t).always(function(){o.updatingGfiSelfTestEnabled(!1)})}),o.groundCheckEnabled.subscribe(function(t){o.updatingGroundCheckEnabled(!0),o.openevse.ground_check(function(e){o.setForTime(o.savedGroundCheckEnabled,2e3),t!==e&&o.groundCheckEnabled(e)},t).always(function(){o.updatingGroundCheckEnabled(!1)})}),o.stuckRelayEnabled.subscribe(function(t){o.updatingStuckRelayEnabled(!0),o.savedStuckRelayEnabled(!1),o.openevse.stuck_relay_check(function(e){o.savedStuckRelayEnabled(!0),setTimeout(function(){o.savedStuckRelayEnabled(!1)},2e3),t!==e&&o.stuckRelayEnabled(e)},t).always(function(){o.updatingStuckRelayEnabled(!1)})}),o.tempCheckEnabled.subscribe(function(t){o.updatingTempCheckEnabled(!0),o.openevse.temp_check(function(e){o.setForTime(o.savedTempCheckEnabled,2e3),t!==e&&o.tempCheckEnabled(e)},t).always(function(){o.updatingTempCheckEnabled(!1)})}),o.diodeCheckEnabled.subscribe(function(t){o.updatingDiodeCheckEnabled(!0),o.openevse.diode_check(function(e){o.setForTime(o.savedDiodeCheckEnabled,2e3),t!==e&&o.diodeCheckEnabled(e)},t).always(function(){o.updatingDiodeCheckEnabled(!1)})}),o.ventRequiredEnabled.subscribe(function(t){o.updatingVentRequiredEnabled(!0),o.openevse.vent_required(function(e){o.setForTime(o.savedVentRequiredEnabled,2e3),t!==e&&o.ventRequiredEnabled(e)},t).always(function(){o.updatingVentRequiredEnabled(!1)})}),i=!0)},o.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};o.updateCount(0),o.nextUpdate(e)},o.nextUpdate=function(e){(0,a[o.updateCount()])().always(function(){o.updateCount(o.updateCount()+1),o.updateCount()<a.length?o.nextUpdate(e):(o.subscribe(),e())})},o.delayTimerValid=ko.pureComputed(function(){return s(o.delayTimerStart())&&s(o.delayTimerStop())}),o.startDelayTimer=function(){o.updatingDelayTimer(!0),o.openevse.timer(function(){o.delayTimerEnabled(!0)},o.delayTimerStart(),o.delayTimerStop()).always(function(){o.updatingDelayTimer(!1)})},o.stopDelayTimer=function(){o.updatingDelayTimer(!0),o.openevse.cancelTimer(function(){o.delayTimerEnabled(!1)}).always(function(){o.updatingDelayTimer(!1)})},o.setStatus=function(e){\"pause\"===e&&(e=o.config.pause_uses_disabled()?\"disable\":\"sleep\");var t=o.status.state();\"disable\"===e&&255===t||\"sleep\"===e&&254===t||\"enable\"===e&&t<254||(o.updatingStatus(!0),!o.delayTimerEnabled()||\"sleep\"!==e&&\"enable\"!==e?o.openevse.status(function(e){o.status.state(e)},e).always(function(){o.updatingStatus(!1)}):o.openevse.press_button(function(){e=!1}).always(function(){o.openevse.status(function(e){o.status.state(e)},e).always(function(){o.updatingStatus(!1)})}))},o.restartFetching=ko.observable(!1),o.restart=function(){confirm(\"Restart OpenEVSE? Current config will be saved, takes approximately 10s.\")&&(o.restartFetching(!0),o.openevse.reset().always(function(){o.restartFetching(!1)}))}}function OpenEvseWiFiViewModel(e,t,n){var o=this;o.baseHost=ko.observable(\"\"!==e?e:\"openevse.local\"),o.basePort=ko.observable(t),o.baseProtocol=ko.observable(n),o.baseEndpoint=ko.pureComputed(function(){var e=\"//\"+o.baseHost();return 80!==o.basePort()&&(e+=\":\"+o.basePort()),e}),o.wsEndpoint=ko.pureComputed(function(){var e=\"ws://\"+o.baseHost();return\"https:\"===o.baseProtocol()&&(e=\"wss://\"+o.baseHost()),80!==o.basePort()&&(e+=\":\"+o.basePort()),e+=\"/ws\"}),o.config=new ConfigViewModel(o.baseEndpoint),o.status=new StatusViewModel(o.baseEndpoint),o.rapi=new RapiViewModel(o.baseEndpoint),o.scan=new WiFiScanViewModel(o.baseEndpoint),o.wifi=new WiFiConfigViewModel(o.baseEndpoint,o.config,o.status,o.scan),o.openevse=new OpenEvseViewModel(o.baseEndpoint,o.config,o.status),o.zones=new ZonesViewModel(o.baseEndpoint),o.schedule=new ScheduleViewModel(o.baseEndpoint),o.initialised=ko.observable(!1),o.updating=ko.observable(!1),o.scanUpdating=ko.observable(!1),o.wifi.selectedNet.subscribe(function(e){!1!==e&&o.config.ssid(e.ssid())}),o.config.ssid.subscribe(function(e){o.wifi.setSsid(e)}),o.showMqttInfo=ko.observable(!1),o.showSolarDivert=ko.observable(!1),o.showSafety=ko.observable(!1),o.showVehiclePauseStatus=ko.observable(!1),o.toggle=function(e){e(!e())},o.advancedMode=ko.observable(!1),o.advancedMode.subscribe(function(e){o.setCookie(\"advancedMode\",e.toString())}),o.developerMode=ko.observable(!1),o.developerMode.subscribe(function(e){o.setCookie(\"developerMode\",e.toString()),e&&o.advancedMode(!0)});var r=null,a=null;o.status.time.subscribe(function(e){o.openevse.time.timeUpdate(new Date(e))}),o.timeSource=ko.computed({read:function(){return o.config.sntp_enabled()?\"ntp\":o.openevse.time.automaticTime()?\"browser\":\"manual\"},write:function(e){switch(e){case\"ntp\":o.config.sntp_enabled(!0),o.openevse.time.automaticTime(!0);break;case\"browser\":o.config.sntp_enabled(!1),o.openevse.time.automaticTime(!0);break;case\"manual\":o.config.sntp_enabled(!1),o.openevse.time.automaticTime(!1)}}}),o.time_zone=ko.computed({read:function(){return o.config.time_zone()},write:function(e){void 0!==e&&!1===o.zones.fetching()&&o.config.time_zone(e)}});n=\"status\";function i(){var e=o.config.emoncms_server().split(\"://\",2);return 1<e.length?e:[o.config.http_supported_protocols()[0],e[0]]}\"\"!==window.location.hash&&(n=window.location.hash.substr(1)),o.tab=ko.observable(n),o.tab.subscribe(function(e){window.location.hash=\"#\"+e}),o.isSystem=ko.pureComputed(function(){return\"system\"===o.tab()}),o.isServices=ko.pureComputed(function(){return\"services\"===o.tab()}),o.isStatus=ko.pureComputed(function(){return\"status\"===o.tab()}),o.isRapi=ko.pureComputed(function(){return\"rapi\"===o.tab()}),o.upgradeUrl=ko.observable(\"about:blank\"),o.wifiPassword=new PasswordViewModel(o.config.pass),o.emoncmsApiKey=new PasswordViewModel(o.config.emoncms_apikey),o.mqttPassword=new PasswordViewModel(o.config.mqtt_pass),o.wwwPassword=new PasswordViewModel(o.config.www_password),o.emoncms_protocol=ko.computed({read:function(){return 0==o.config.http_supported_protocols().length?\"\":i()[0]},write:function(e){0<o.config.http_supported_protocols().length&&o.config.emoncms_server(e+\"://\"+i()[1])}}),o.emoncms_server=ko.computed({read:function(){return 0==o.config.http_supported_protocols().length?o.config.emoncms_server():i()[1]},write:function(e){var t,n;0<o.config.http_supported_protocols().length?(t=(1<(n=e.split(\"://\",2)).length?n:i())[0],n=1<n.length?n[1]:e,o.config.emoncms_server(t+\"://\"+n)):o.config.emoncms_server(e)}}),o.config.mqtt_protocol.subscribe(function(e){switch(e){case\"mqtt\":\"8883\"==o.config.mqtt_port()&&o.config.mqtt_port(\"1883\");break;case\"mqtts\":\"1883\"==o.config.mqtt_port()&&o.config.mqtt_port(\"8883\")}}),o.loadedCount=ko.observable(0),o.itemsLoaded=ko.pureComputed(function(){return o.loadedCount()+o.openevse.updateCount()}),o.itemsTotal=ko.observable(3+o.openevse.updateTotal()),o.start=function(){o.updating(!0),o.status.update(function(){o.loadedCount(o.loadedCount()+1),o.config.update(function(){o.loadedCount(o.loadedCount()+1),o.schedule.update(function(){o.loadedCount(o.loadedCount()+1),o.baseHost().endsWith(\".local\")&&\"\"!==o.status.ipaddress()&&(\"\"===o.config.www_username()?o.baseHost(o.status.ipaddress()):window.location.replace(\"http://\"+o.status.ipaddress()+\":\"+o.basePort())),o.status.rapi_connected()?o.openevse.update(o.finishedStarting):(o.finishedStarting(),o.status.rapi_connected.subscribe(function(e){e&&o.config.update(function(){o.openevse.update(function(){})})}))})}),o.connect()}),o.advancedMode(\"true\"===o.getCookie(\"advancedMode\",\"false\")),o.developerMode(\"true\"===o.getCookie(\"developerMode\",\"false\"))},o.finishedStarting=function(){o.initialised(!0),r=setTimeout(o.update,5e3),o.upgradeUrl(o.baseEndpoint()+\"/update\");for(var e=document.getElementsByTagName(\"img\"),t=0;t<e.length;t++)e[t].getAttribute(\"data-src\")&&e[t].setAttribute(\"src\",e[t].getAttribute(\"data-src\"));!1!==o.config.time_zone()&&(o.zones.initialValue(o.config.time_zone()),o.zones.update(function(){o.config.time_zone.valueHasMutated()})),o.updating(!1)};var s=!(o.update=function(){o.updating()||(o.updating(!0),null!==r&&(clearTimeout(r),r=null),o.status.update(function(){r=setTimeout(o.update,5e3),o.updating(!1)}))});o.startScan=function(){o.scanUpdating()||(s=!0,o.scanUpdating(!0),null!==a&&(clearTimeout(a),a=null),o.scan.update(function(){s&&(a=setTimeout(o.startScan,3e3)),o.scanUpdating(!1)}))},o.stopScan=function(){s=!1,o.scanUpdating()||null!==a&&(clearTimeout(a),a=null)},o.wifiConnecting=ko.observable(!1),o.status.mode.subscribe(function(e){\"STA+AP\"!==e&&\"STA\"!==e||o.wifiConnecting(!1),\"STA+AP\"===e||\"AP\"===e?o.startScan():o.stopScan()}),o.saveNetworkFetching=ko.observable(!1),o.saveNetworkSuccess=ko.observable(!1),o.saveNetwork=function(){\"\"===o.config.ssid()?alert(\"Please select network\"):(o.saveNetworkFetching(!0),o.saveNetworkSuccess(!1),$.post(o.baseEndpoint()+\"/savenetwork\",{ssid:o.config.ssid(),pass:o.config.pass()},function(){o.saveNetworkSuccess(!0),o.wifiConnecting(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){o.saveNetworkFetching(!1)}))},o.saveAdminFetching=ko.observable(!1),o.saveAdminSuccess=ko.observable(!1),o.saveAdmin=function(){o.saveAdminFetching(!0),o.saveAdminSuccess(!1),$.post(o.baseEndpoint()+\"/saveadmin\",{user:o.config.www_username(),pass:o.config.www_password()},function(){o.saveAdminSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){o.saveAdminFetching(!1)})},o.advancedGroup=new ConfigGroupViewModel(o.baseEndpoint,function(){return{hostname:o.config.hostname(),sntp_hostname:o.config.sntp_hostname()}}).done(function(){confirm(\"These changes require a reboot to take effect. Reboot now?\")&&$.post(o.baseEndpoint()+\"/restart\",{},function(){setTimeout(function(){var e=\"http://\"+o.config.hostname()+\".local\";80!=o.basePort()&&(e+=\":\"+o.basePort()),e+=\"/\",window.location.replace(e)},5e3)}).fail(function(){alert(\"Failed to restart\")})}),o.saveEmonCmsFetching=ko.observable(!1),o.saveEmonCmsSuccess=ko.observable(!1),o.saveEmonCms=function(){var e={enable:o.config.emoncms_enabled(),server:o.config.emoncms_server(),apikey:o.config.emoncms_apikey(),node:o.config.emoncms_node(),fingerprint:o.config.emoncms_fingerprint()};!e.enable||\"\"!==e.server&&\"\"!==e.node?e.enable&&32!==e.apikey.length&&!o.emoncmsApiKey.isDummy()?alert(\"Please enter valid Emoncms apikey\"):e.enable&&\"\"!==e.fingerprint&&59!==e.fingerprint.length?alert(\"Please enter valid SSL SHA-1 fingerprint\"):(o.saveEmonCmsFetching(!0),o.saveEmonCmsSuccess(!1),$.post(o.baseEndpoint()+\"/saveemoncms\",e,function(){o.saveEmonCmsSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){o.saveEmonCmsFetching(!1)})):alert(\"Please enter Emoncms server and node\")},o.mqttGroup=new ConfigGroupViewModel(o.baseEndpoint,function(){return{mqtt_enabled:o.config.mqtt_enabled(),divert_enabled:o.config.divert_enabled(),mqtt_protocol:o.config.mqtt_protocol(),mqtt_server:o.config.mqtt_server(),mqtt_port:o.config.mqtt_port(),mqtt_reject_unauthorized:o.config.mqtt_reject_unauthorized(),mqtt_topic:o.config.mqtt_topic(),mqtt_user:o.config.mqtt_user(),mqtt_pass:o.config.mqtt_pass(),mqtt_vrms:o.config.mqtt_vrms()}}).validate(function(e){return o.config.mqtt_enabled()||o.config.divert_enabled(!1),!e.mqtt_enabled||\"\"!==e.mqtt_server||(alert(\"Please enter MQTT server\"),!1)}),o.vehicleGroup=new ConfigGroupViewModel(o.baseEndpoint,function(){return{pause_uses_disabled:o.config.pause_uses_disabled()}}),o.config.pause_uses_disabled.subscribe(function(){o.vehicleGroup.save()}),o.divertGroup=new ConfigGroupViewModel(o.baseEndpoint,function(){return{divert_enabled:o.config.divert_enabled(),mqtt_solar:o.config.mqtt_solar(),mqtt_grid_ie:o.config.mqtt_grid_ie(),divert_PV_ratio:o.config.divert_PV_ratio(),divert_attack_smoothing_factor:o.config.divert_attack_smoothing_factor(),divert_decay_smoothing_factor:o.config.divert_decay_smoothing_factor(),divert_min_charge_time:o.config.divert_min_charge_time()}}).validate(function(e){return!e.divert_enabled||\"\"!==e.mqtt_solar||\"\"!==e.mqtt_grid_ie||(alert(\"Please enter either a Solar PV or Grid I/E feed\"),!1)}),o.chargeMode=new ConfigGroupViewModel(o.baseEndpoint,function(){return{charge_mode:o.config.charge_mode()}}),o.isEcoModeAvailable=ko.pureComputed(function(){return o.config.mqtt_enabled()&&(\"\"!==o.config.mqtt_solar()||\"\"!==o.config.mqtt_grid_ie())}),o.ecoMode=ko.pureComputed({read:function(){return\"eco\"===o.config.charge_mode()},write:function(e){o.config.charge_mode(e&&o.config.divert_enabled()?\"eco\":\"fast\"),o.chargeMode.save()}}),o.status.divertmode.subscribe(function(e){switch(e){case 1:o.config.charge_mode(\"fast\");break;case 2:o.config.charge_mode(\"eco\")}}),o.haveSolar=ko.pureComputed(function(){return\"\"!==o.config.mqtt_solar()}),o.haveGridIe=ko.pureComputed(function(){return\"\"!==o.config.mqtt_grid_ie()}),o._divertFeedType=\"grid_ie\",o.divertFeedType=ko.computed({read:function(){var e=o.haveSolar()?\"solar\":o.haveGridIe()?\"grid_ie\":o._divertFeedType;return o._divertFeedType=e},write:function(e){\"solar\"===e&&o.haveGridIe()?(o.config.mqtt_solar(o.config.mqtt_grid_ie()),o.config.mqtt_grid_ie(\"\")):\"grid_ie\"===e&&o.haveSolar()&&(o.config.mqtt_grid_ie(o.config.mqtt_solar()),o.config.mqtt_solar(\"\")),o._divertFeedType=e}}),o.divertFeedValue=ko.computed({read:function(){return\"solar\"===o.divertFeedType()?o.config.mqtt_solar():o.config.mqtt_grid_ie()},write:function(e){\"solar\"===o.divertFeedType()?o.config.mqtt_solar(e):o.config.mqtt_grid_ie(e)}}),o.saveOhmKeyFetching=ko.observable(!1),o.saveOhmKeySuccess=ko.observable(!1),o.saveOhmKey=function(){o.saveOhmKeyFetching(!0),o.saveOhmKeySuccess(!1),$.post(o.baseEndpoint()+\"/saveohmkey\",{enable:o.config.ohm_enabled(),ohm:o.config.ohmkey()},function(){o.saveOhmKeySuccess(!0)}).fail(function(){alert(\"Failed to save Ohm key config\")}).always(function(){o.saveOhmKeyFetching(!1)})},o.setTimeFetching=ko.observable(!1),o.setTimeSuccess=ko.observable(!1),o.setTime=function(){o.setTimeFetching(!0),o.setTimeSuccess(!1);var e,t,n=o.openevse.time.automaticTime()?new Date:o.openevse.time.evseTimedate();0==o.status.time()?o.openevse.openevse.time(function(e){var t=!(1<arguments.length&&void 0!==arguments[1])||arguments[1];o.setTimeFetching(!1),o.setTimeSuccess(t),o.openevse.time.timeUpdate(e,t)},n):(!(t={ntp:e=o.config.sntp_enabled(),tz:o.time_zone()})===e&&(t.time=n.toISOString()),$.post(o.baseEndpoint()+\"/settime\",t,function(){o.setTimeFetching(!1),o.setTimeSuccess(!0)}).fail(function(){alert(\"Failed to set time\"),o.setTimeFetching(!1)}))},o.turnOffAccessPointFetching=ko.observable(!1),o.turnOffAccessPointSuccess=ko.observable(!1),o.turnOffAccessPoint=function(){o.turnOffAccessPointFetching(!0),o.turnOffAccessPointSuccess(!1),$.post(o.baseEndpoint()+\"/apoff\",{},function(e){console.log(e),\"\"!==o.status.ipaddress()?setTimeout(function(){window.location=\"http://\"+o.status.ipaddress(),o.turnOffAccessPointSuccess(!0)},3e3):o.turnOffAccessPointSuccess(!0)}).fail(function(){alert(\"Failed to turn off Access Point\")}).always(function(){o.turnOffAccessPointFetching(!1)})},o.factoryResetFetching=ko.observable(!1),o.factoryResetSuccess=ko.observable(!1),o.factoryReset=function(){confirm(\"CAUTION: Do you really want to Factory Reset? All setting and config will be lost.\")&&(o.factoryResetFetching(!0),o.factoryResetSuccess(!1),$.post(o.baseEndpoint()+\"/reset\",{},function(){o.factoryResetSuccess(!0)}).fail(function(){alert(\"Failed to Factory Reset\")}).always(function(){o.factoryResetFetching(!1)}))},o.restartFetching=ko.observable(!1),o.restartSuccess=ko.observable(!1),o.restart=function(){confirm(\"Restart OpenEVSE WiFi? Current config will be saved, takes approximately 10s.\")&&(o.restartFetching(!0),o.restartSuccess(!1),$.post(o.baseEndpoint()+\"/restart\",{},function(){o.restartSuccess(!0)}).fail(function(){alert(\"Failed to restart\")}).always(function(){o.restartFetching(!1)}))},o.updateFetching=ko.observable(!1),o.updateComplete=ko.observable(!1),o.updateError=ko.observable(\"\"),o.updateFilename=ko.observable(\"\"),o.updateLoaded=ko.observable(0),o.updateTotal=ko.observable(1),o.updateProgress=ko.pureComputed(function(){return o.updateLoaded()/o.updateTotal()*100}),o.otaUpdate=function(){var e;\"\"!==o.updateFilename()?(o.updateFetching(!0),o.updateError(\"\"),e=$(\"#upload_form\")[0],e=new FormData(e),$.ajax({url:\"/update\",type:\"POST\",data:e,contentType:!1,processData:!1,xhr:function(){var e;return(e=new window.XMLHttpRequest).upload.addEventListener(\"progress\",function(e){e.lengthComputable&&(o.updateLoaded(e.loaded),o.updateTotal(e.total))},!1),e}}).done(function(e){console.log(e),\"OK\"==e?o.updateComplete(!0):o.updateError(e)}).fail(function(){o.updateError(\"HTTP Update failed\")}).always(function(){o.updateFetching(!1)})):o.updateError(\"Filename not set\")},o.pingInterval=!1,o.reconnectInterval=!1,o.socket=!1,o.connect=function(){o.socket=new WebSocket(o.wsEndpoint()),o.socket.onopen=function(e){console.log(e),o.pingInterval=setInterval(function(){o.socket.send('{\"ping\":1}')},1e3)},o.socket.onclose=function(e){console.log(e),o.reconnect()},o.socket.onmessage=function(e){console.log(e),ko.mapping.fromJSON(e.data,o.status)},o.socket.onerror=function(e){console.log(e),o.socket.close(),o.reconnect()}},o.reconnect=function(){!1!==o.pingInterval&&(clearInterval(o.pingInterval),o.pingInterval=!1),!1===o.reconnectInterval&&(o.reconnectInterval=setTimeout(function(){o.reconnectInterval=!1,o.connect()},500))},o.setCookie=function(e,t){var n,o=2<arguments.length&&void 0!==arguments[2]&&arguments[2],r=\"\";!1!==o&&((n=new Date).setTime(n.getTime()+24*o*60*60*1e3),r=\";expires=\"+n.toUTCString()),document.cookie=e+\"=\"+t+r+\";path=/\"},o.getCookie=function(e){for(var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\",n=e+\"=\",o=document.cookie.split(\";\"),r=0;r<o.length;r++){for(var a=o[r];\" \"===a.charAt(0);)a=a.substring(1);if(0===a.indexOf(n))return a.substring(n.length,a.length)}return t}}function scaleString(e,t,n){return((\"number\"==typeof e?e:parseInt(e))/t).toFixed(n)}function formatUpdate(e){if(!1===e)return\"N/A\";var t=e/60,n=e/3600,o=n/24,r=e.toFixed(0)+\"s\";return 0===e.toFixed(0)?r=\"now\":7<o?r=\"inactive\":2<o?r=o.toFixed(1)+\" days\":2<n?r=n.toFixed(0)+\" hrs\":180<e&&(r=t.toFixed(0)+\" mins\"),r}function updateClass(e){if(!1===e)return\"\";var t=\"updateBad\";return(e=Math.abs(e))<25?t=\"updateGood\":e<60?t=\"updateSlow\":e<7200&&(t=\"updateSlower\"),t}!function(){var t=window.location.hostname,n=window.location.port,o=window.location.protocol;$(function(){var e=new OpenEvseWiFiViewModel(t,n,o);ko.applyBindings(e),e.start()})}();\n"
  "//# sourceMappingURL=home.js.map\n";
