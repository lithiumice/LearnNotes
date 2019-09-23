from selenium.webdriver import Remote
from selenium.webdriver.chrome import options
from selenium.common.exceptions import InvalidArgumentException


class ReuseChrome(Remote):
    def __int__(self, session_id, command_executor):
        self.r_session_id = session_id
        Remote.__init__(command_executor=command_executor, desired_capabilities={}, browser_profile=None, proxy=None,
                 keep_alive=False, file_detector=None, options=None)


    def start_session(self, capabilities, browser_profile=None):
        if not isinstance(capabilities, dict):
            pass
            # raise InvalidArgumentException("capabilities must be a dictionary")
        if browser_profile:
            if "moz:firefoxOption" in capabilities:
                capabilities["moz:firefoxOption"]["profile"] = browser_profile.encoded
            else:
                capabilities.update({'firefox_profile': browser_profile.encoded})
        self.capabilities = options.Options().to_capabilities()
        self.session_id = self.r_session_id
        self.w3c = False
